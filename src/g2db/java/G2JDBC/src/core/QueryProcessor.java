package core;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSetMetaData;
import java.sql.Statement;
import java.sql.CallableStatement;
import java.sql.SQLException;
import java.sql.ResultSet;
import java.util.Enumeration;
import java.util.Queue;
import java.util.Map;
import java.util.HashMap;
import java.util.LinkedList;

import exception.ErrorMessage;
import exception.InfoMessage;
import exception.WarningMessage;

import type.ReturnUpdateControlValues;
import type.StatusTuple;
import type.StatusSymbol;
import type.MultipleValuesFactory;

import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.MultipleValuesHolder;
import com.gensym.classes.G2Array;
import com.gensym.classes.G2List;
import com.gensym.classes.Item;
import com.gensym.classes.ItemArray;
import com.gensym.classes.ItemList;
import com.gensym.classes.SymbolArray;
import com.gensym.classes.SymbolList;
import com.gensym.classes.TextList;
import com.gensym.classes.TextListImpl;
import com.gensym.classes.modules.g2database.DbCursorObject;
import com.gensym.classes.modules.g2database.DbQueryItem;
import com.gensym.classes.modules.g2database.DbQueryItemArray;
import com.gensym.classes.modules.g2database.DbQueryItemList;
import com.gensym.classes.modules.g2database.DbSqlObject;
import com.gensym.util.NoSuchAttributeException;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;
import com.gensym.jgi.download.G2StubCreationException;
import com.gensym.jgi.download.G2StubResolver;
import config.BridgeParameters;
import config.ProcessParameters;

/**
 * This class handles data flow between bridge core and JDBC driver
 * @author SoftServe
 *
 */
public class QueryProcessor {

	/**
	 * Connection to underlying database
	 */
	private Connection dbcon;
	/**
	 * Events logger
	 */
	private BridgeEventsLogger logger = null;
	/**
	 * SQL statements which should be committed on next dbCommit call
	 */
	private Queue<String> pendingPlainSQLStatements = null;
	/**
	 * Prepared SQL statements which should be committed on next dbCommit call
	 */
	private Queue<PreparedStatement> pendingPreparedStatements = null;
	/**
	 * Defined by user SQL objects
	 */
	private Map<DbSqlObject, PreparedStatement> definedSQLObjects = null;
	/**
	 * Defined by user cursor objects
	 */
	private Map<DbCursorObject, PreparedStatement> preparedCursorObjects = null;
	/**
	 * This bridge parameters
	 */
	private BridgeParameters bridgeParameters = null;
	/**
	 * Additional bridge parameters
	 */
	private ProcessParameters processParameters = null;
	/**
	 * Charset converter to database encoding
	 */
	private CharsetMapper dbCharset = null;
	/**
	 * Charset converter to host encoding
	 */
	private CharsetMapper hostCharset = null;
	/**
	 * Value which substitutes SQL NULL on binding
	 */
	private Object nullBindRepalcement = null;
	/**
	 * Value which substitutes SQL NULL on fetching
	 */
	private Object nullFetchReplacement = null;
	private G2JDBCBridge application = null;
	
	/**
	 * Creates new QueryProcessor
	 * @param con underlying database connection
	 * @param logger logger for handling all processor events
	 * @param bp bridge parameters
	 * @param pp process parameters
	 */
	public QueryProcessor(Connection con, BridgeEventsLogger logger,
			BridgeParameters bp, ProcessParameters pp, G2JDBCBridge app) {

		dbcon = con;
		bridgeParameters = bp;
		application = app;
		processParameters = pp;
		this.logger = logger;
		pendingPlainSQLStatements = new LinkedList<String> ();
		pendingPreparedStatements = new LinkedList<PreparedStatement> ();
		definedSQLObjects = new HashMap<DbSqlObject, PreparedStatement> ();
		preparedCursorObjects = new HashMap<DbCursorObject, PreparedStatement>();
		dbCharset = new CharsetMapper(bp.getCharset());
		hostCharset = new CharsetMapper("ISO-8859-1");
	}
	
	public void setNullBindRepalcement(Object nullBindRepalcement) {
		this.nullBindRepalcement = nullBindRepalcement;
	}

	public void setNullFetchReplacement(Object nullFetchReplacement) {
		this.nullFetchReplacement = nullFetchReplacement;
	}
	
	/**
	 * Prepares database cursor and binds variables to it
	 * @param cursor database cursor
	 * @param sql SQL statement
	 * @param values values to bind
	 * @return new PreparedStatement for the cursor
	 * @throws SQLException when PreparedStatement can not be created
	 * @throws G2AccessException when variables binding fails
	 */
	public PreparedStatement prepareAndBind(final DbCursorObject cursor, final String sql, final TextList values) throws SQLException, G2AccessException {
		PreparedStatement stmt;
		String sqlQuery = sql.replaceAll(":\\w+", "?");
		sqlQuery = dbCharset.convertToThisCharset(sqlQuery);
		if (preparedCursorObjects.containsKey(cursor)) {
			preparedCursorObjects.get(cursor).close();
			preparedCursorObjects.remove(cursor);
		}
		stmt = dbcon.prepareStatement(sqlQuery, ResultSet.TYPE_SCROLL_INSENSITIVE,ResultSet.CONCUR_READ_ONLY,
				ResultSet.HOLD_CURSORS_OVER_COMMIT);
		preparedCursorObjects.put(cursor, stmt);
		bindVariables(stmt, values);
		return stmt;
	}
	/**
	 * Executes query using given cursor
	 * @param cursor cursor to execute query on
	 * @return ResultSet with query execution result
	 * @throws SQLException when execution fails
	 */
	public ResultSet performQueryOnCursor(DbCursorObject cursor) throws SQLException{
		PreparedStatement ps = preparedCursorObjects.get(cursor);
		ps.execute();
		return ps.getResultSet();
	}
	/**
	 * Fetches column names from given result set
	 * @param rs ResultSet to fetch columns from
	 * @return Sequence with columns names
	 * @throws SQLException when accessing ResultSet fails
	 */
	public Sequence getColumnNames(ResultSet rs) throws SQLException {
		Sequence colummnNamesSeq = new Sequence ();
		ResultSetMetaData rsmd = rs.getMetaData();
		for (int i = 1; i <= rsmd.getColumnCount(); i++) {
			String columnName = hostCharset.convertToThisCharset(rsmd.getColumnName(i));
			colummnNamesSeq.add(Symbol.intern(columnName.toUpperCase()));
		}
		return colummnNamesSeq;
	}
	/**
	 * Fetches row values as sequence from given result set
	 * @param rs ResultSet to fetch values from
	 * @param fetchBatch maximum rows count to fetch
	 * @return rows values sequence
	 * @throws SQLException when reading from ResultSet fails
	 * @throws G2AccessException when writing to Sequence fails
	 */
	public Sequence getRowValues(ResultSet rs, int fetchBatch) throws SQLException, G2AccessException {
		Sequence resultSeq = new Sequence ();
		ResultSetMetaData rsmd = rs.getMetaData();
		int recordsToFetch;
		if (fetchBatch == 0) {
			recordsToFetch = Integer.parseInt(bridgeParameters.getMaxrows());
		} else {
			recordsToFetch = fetchBatch;
		}
		for (int i = 1; i <= recordsToFetch; i++) {
			if (!rs.next()) {
				break;
			}
			Sequence rowValuesSequence = new Sequence();
			for (int j = 1; j <= rsmd.getColumnCount(); j++) {
				Object obj = rs.getObject(j);
				if (obj == null) {
					obj = nullFetchReplacement;
				}
				if (obj instanceof String) {
					obj = hostCharset.convertToThisCharset((String)obj);
				}
				rowValuesSequence.add(obj);
			}
			resultSeq.add(rowValuesSequence);
		}
		return resultSeq;
	}
	
	/**
	 * Fetches column values from given result set
	 * @param rs ResultSet to fetch column values from
	 * @param fetchBatch maximum count of fetched columns
	 * @return Sequence with column values
	 * @throws SQLException when reading from ResultSet fails
	 * @throws G2AccessException when writing to Sequence fails
	 */
	public Sequence getColumnValues(ResultSet rs, int fetchBatch) throws SQLException, G2AccessException {
		Sequence resultSeq = new Sequence ();
		ResultSetMetaData rsmd = rs.getMetaData();
		int i;
		int recordsToFetch;
		if (fetchBatch == 0) {
			recordsToFetch = Integer.parseInt(bridgeParameters.getMaxrows());
		} else {
			recordsToFetch = fetchBatch;
		}
		int columnCount = rsmd.getColumnCount();
		for (i = 1; i <= columnCount; i++) {
			resultSeq.add(new Sequence());
		}
		for (i = 1; i <= recordsToFetch; i++) {
			if (!rs.next()) {
				break;
			}
			for (int j = 1; j <= columnCount; j++) {
				Object obj = rs.getObject(j);
				if (obj == null) {
					obj = nullFetchReplacement;
				}
				if (obj instanceof String) {
					obj = hostCharset.convertToThisCharset((String)obj);
				}
				((Sequence)resultSeq.get(j-1)).add(obj);
			}
		}
		return resultSeq;
	}
	/**
	 * Executes stored procedure which is assumed to return a value
	 * @param procName stored procedure name
	 * @param arguments stored procedure arguments
	 * @return first value in the first ResultSet row
	 * @throws SQLException when accessing ResultSet fails
	 */
	public MultipleValuesHolder executeStoredProcedureReturningValue(String procName, String arguments) throws SQLException {
		String fullCall = "{call " + procName + "(" + arguments + ")}";
		fullCall = dbCharset.convertToThisCharset(fullCall);
		String rv = null;
		CallableStatement cs = dbcon.prepareCall(fullCall, ResultSet.TYPE_SCROLL_INSENSITIVE,
					ResultSet.HOLD_CURSORS_OVER_COMMIT);
		ResultSet rs = cs.executeQuery();
		boolean hasReturnValue = rs.first();
		if (hasReturnValue) {
			rv = rs.getString(1);
			rv = hostCharset.convertToThisCharset((String)rv);
		} else {
				logger.warning(WarningMessage.STORED_PROC_RET_NO_VALUE);
				return MultipleValuesFactory.create4("", StatusSymbol.WARNING, 0, WarningMessage.STORED_PROC_RET_NO_VALUE);
		}
		logger.info(InfoMessage.STORED_PROC_RET_OK);
		return MultipleValuesFactory.create4(rv, StatusSymbol.SUCCESS, 0, InfoMessage.STORED_PROC_RET_OK);
	}
	
	/**
	 * Executes stored procedure which is not supposed to return a value
	 * @param procCall full procedure signature with arguments
	 * @return execution result as multiple values object
	 * @throws SQLException when accessing ResultSet fails
	 */
	public MultipleValuesHolder executeStoredProcedure(String procCall) throws SQLException {
		StatusTuple result = null;
		String fullCall = "{call " + procCall + "}";
		fullCall = dbCharset.convertToThisCharset(fullCall);
		CallableStatement cs = dbcon.prepareCall(fullCall);
		cs.executeQuery();
		return MultipleValuesFactory.create3(StatusSymbol.SUCCESS, 0, InfoMessage.SQL_EXEC_OK);
	}
	/**
	 * Executes SQL statement which is not supposed to return values
	 * @param sql SQL statement to execute
	 * @param autoCommit if true, execution will be immediate, 
	 * otherwise SQL statement will be pending next dbCommit call
	 * @return execution status as StatusTuple
	 */
	public MultipleValuesHolder executePlainSQL
	 (final String sql, final boolean autoCommit) throws SQLException  {
		String sqlQuery = dbCharset.convertToThisCharset(sql);
		logger.info(InfoMessage.EXEC_PLAIN_SQL);
		if (autoCommit) {
			Statement s = null;
			s = dbcon.createStatement();
			s.executeUpdate(sqlQuery);
		} else {
			logger.info(InfoMessage.CACHING_SQL);
			pendingPlainSQLStatements.add(sqlQuery);
		}
		return MultipleValuesFactory.create3(StatusSymbol.SUCCESS, 0, InfoMessage.EXEC_IMM_OK);
	}
	/**
	 * Executes SQL function (statement which is supposed to return a single value)
	 * @param stmnt SQL function to execute
	 * @return execution result as multiple values 
	 * @throws SQLException when accessing ResultSet fails
	 */
	public MultipleValuesHolder executeSQLFunction(final String stmnt) throws SQLException {
		String sretval = null;
		Float fretval = null;
		Statement s = dbcon.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE,
				ResultSet.HOLD_CURSORS_OVER_COMMIT);
		String sqlQuery = dbCharset.convertToThisCharset(stmnt);
		ResultSet rs = s.executeQuery(sqlQuery);
		rs.beforeFirst();
		if (rs.next()) {
			String retval = rs.getString(1);
			try {
				fretval = Float.parseFloat(retval);
				sretval = null;
			} catch (NumberFormatException nfe) {
				fretval = null;
				sretval = retval;
			}
			return MultipleValuesFactory.create5(fretval, sretval, StatusSymbol.SUCCESS,
						0, InfoMessage.SQL_FUNCTION_OK);
		} else {
			return MultipleValuesFactory.create5(null, null,
					StatusSymbol.WARNING, 0, WarningMessage.SQL_FUNC_RET_NULL);
		}
	}
	/**
	 * Defines SQL object for further usage in this bridge context
	 * @param dso SQL object to be defined
	 * @param st SQL statement which is related to this SQL object
	 * @param tl values for binding variables in this SQL object
	 * @return execution result as multiple values 
	 */
	public MultipleValuesHolder defineSQL(final DbSqlObject dso, final String st, final TextList tl)
		throws SQLException, G2AccessException {
		boolean alreadyDefined = definedSQLObjects.containsKey(dso);
		PreparedStatement ps = null;
		String sqlQuery = st.replaceAll(":\\w+", "?");
		sqlQuery = dbCharset.convertToThisCharset(sqlQuery);
		ps = dbcon.prepareStatement(sqlQuery, ResultSet.TYPE_SCROLL_INSENSITIVE,ResultSet.CONCUR_READ_ONLY,
					ResultSet.HOLD_CURSORS_OVER_COMMIT);
		bindVariables(ps, tl);
		if (alreadyDefined) {
			definedSQLObjects.remove(dso);
		} 
		definedSQLObjects.put(dso, ps);
		return MultipleValuesFactory.create3(StatusSymbol.SUCCESS, 0, InfoMessage.SQL_DEFINED);
	}
	/**
	 * Updates defined SQL object
	 * @param dso Instance of the defined SQL object
	 * @param values values which should be rebound in this update scope
	 * @return execution result as multiple values object
	 */
	public MultipleValuesHolder updateSQL(DbSqlObject dso, TextList values)
	throws G2AccessException, SQLException {
		PreparedStatement ps = definedSQLObjects.get(dso);
		if (ps == null) {
			return MultipleValuesFactory.create3(StatusSymbol.ERROR, 0, ErrorMessage.STATEMENT_NOT_FOUND);
		}
		bindVariables(ps, values);
		return MultipleValuesFactory.create3(StatusSymbol.SUCCESS, 0, InfoMessage.SQL_UPDATED);
	}
	/**
	 * Executes defined SQL object
	 * @param dbso Already defined SQL object which should be executed
	 * @param autoCommit if true, execution will be immediate, otherwise
	 * it will be pending dbCommit call
	 * @return execution result as multiple values object
	 * @throws SQLException when accessing ResultSet fails
	 */
	public MultipleValuesHolder execSQL(DbSqlObject dbso, boolean autoCommit) throws SQLException {
		PreparedStatement ps = definedSQLObjects.get(dbso);
		int affectedRows = 0;
		int dummyValue = 0; //corresponds to xxx in g2-database.kb
		if (autoCommit) {
				boolean hasResultSet = ps.execute();
				if (hasResultSet) {
					ResultSet rs = ps.getResultSet();
					rs.beforeFirst();
					while(rs.next()) {
						affectedRows++;
					}
				} else  {
					affectedRows = ps.getUpdateCount();
				}
				return MultipleValuesFactory.create5(StatusSymbol.SUCCESS,
						0, InfoMessage.SQL_EXEC_OK, dummyValue, affectedRows);
		} else {
			pendingPreparedStatements.add(ps);
		}
		return MultipleValuesFactory.create5(StatusSymbol.SUCCESS,
				0, InfoMessage.SQL_QUEUED_OK, dummyValue, affectedRows);
	}
	/**
	 * Updates given SQL object
	 * @param sqlObject SQL object to update
	 * @param vs binding values as string
	 * @param obj binding values holder
	 * @param ac auto commit flag
	 * @return execution result as multiple values object
	 * @throws G2AccessException when writing to Sequence fails
	 * @throws SQLException when variables binding fails
	 */
	public MultipleValuesHolder updateSQLObject(DbSqlObject sqlObject, String vs, Object obj, boolean ac) throws G2AccessException, SQLException {
		String[] vars = vs.split(",");
		TextList values = new TextListImpl();
		values.setG2ListSequence(new Sequence());
		com.gensym.classes.Object userObject = (com.gensym.classes.Object)obj;
		for (int i = 0; i < vars.length; i++) {
			Symbol attrName = Symbol.intern(vars[i]);
			try {
				Object attribute = (Object)userObject.getPropertyValue(attrName);
				if (attribute != null) {
					if (attribute instanceof G2List) {
						values.getG2ListSequence().add(((G2List)attribute).getG2ListSequence().firstElement());
					} else {
						values.getG2ListSequence().add(attribute);
					}
				}
			} catch (NoSuchAttributeException e) {
				
			}
		} 
		PreparedStatement ps = definedSQLObjects.get(sqlObject);
		if (ps == null) {
			return MultipleValuesFactory.create3(StatusSymbol.ERROR, 0, ErrorMessage.UPDATE_SQL_OBJECT_FAILED);
		}
		bindVariables(ps, values);
		return MultipleValuesFactory.create3(StatusSymbol.SUCCESS, 0, InfoMessage.UPDATE_SQL_OBJECT_OK);
	}
	
	/**
	 * Commits pending queries.
	 * @return commit status as multiple values object
	 */
	public MultipleValuesHolder commitPendingQueries() throws SQLException {
		MultipleValuesHolder result = null;
		String query = pendingPlainSQLStatements.poll();
		int plainCommitsCount = 0;
		logger.info(InfoMessage.COMM_PPLAIN_Q);
		while(null != query) {
			result = executePlainSQL(query, true);
			if (!StatusSymbol.SUCCESS.equals(result.getFirst())) {
				return result;
			}
			plainCommitsCount++;
			query = pendingPlainSQLStatements.poll();
		}
		logger.info(InfoMessage.AMOUNT_OF_COMM_PLAIN_Q + plainCommitsCount);
		//prepared statements part
		int prepCommitsCount = 0;
		logger.info(InfoMessage.COMM_PREP_Q);
		PreparedStatement ps = pendingPreparedStatements.poll();
		while (null != ps) {
			ps.execute();
			prepCommitsCount++;
			ps = pendingPreparedStatements.poll();
		}
		logger.info(InfoMessage.AMOUNT_OF_COMM_PREP_Q + prepCommitsCount);
		return MultipleValuesFactory.create3(StatusSymbol.SUCCESS, 0, InfoMessage.DB_COMMIT_OK);
	}
	/**
	 * Flushes queues with pending queries 
	 * @return success in any case
	 */
	public StatusTuple cancelPendingQueries () {
		logger.info(InfoMessage.CANCELLING_SQL);
		pendingPlainSQLStatements.clear();
		pendingPreparedStatements.clear();
		return new StatusTuple(StatusSymbol.SUCCESS, 0, InfoMessage.SQL_CANCELLED);
	}
	/**
	 * Defines cursor object
	 * @param cursor cursor to be defined
	 * @param sql SQL Statement related to the cursor
	 * @param tl variables to bind for this cursor object
	 * @return execution result as multiple values 
	 * @throws G2AccessException when prepareAndBind call fails
	 * @throws SQLException hen prepareAndBind call fails
	 */
	public MultipleValuesHolder dbDefineCursor(final DbCursorObject cursor, final String sql, final TextList tl) throws SQLException, G2AccessException { 
		String sqlQuery = dbCharset.convertToThisCharset(sql);
		prepareAndBind(cursor, sqlQuery, tl);
		logger.info(InfoMessage.CURSOR_DEFINED);
		return MultipleValuesFactory.create3(StatusSymbol.SUCCESS, 0, "");
	}
	/**
	 * Modifies given database cursor
	 * @param cursor Cursor to be modified
	 * @param sql SQL statement
	 * @param tl text values as TextList
	 * @return operation result as a multiple values object
	 */
	public MultipleValuesHolder dbSetCursor(final DbCursorObject cursor, final String sql, final TextList tl) throws SQLException, G2AccessException { 
		String sqlQuery = dbCharset.convertToThisCharset(sql);
		prepareAndBind(cursor, sqlQuery, tl);
		logger.info(InfoMessage.CURSOR_SET);
		return MultipleValuesFactory.create3(StatusSymbol.SUCCESS, 0, "");
	}
	
	/**
	 * Does nothing
	 * @param cursor ignored
	 * @return success
	 */
	public MultipleValuesHolder dbRefreshCursor(DbCursorObject cursor) {
		return MultipleValuesFactory.create3(StatusSymbol.SUCCESS, 0, "");
	}
	/**
	 * Fetches a specified number of rows (records) from a database cursor and returns
     * them directly to the attributes of a specified object in G2
	 * @param cursor database cursor to start fetching from
	 * @param queryObject object to return values in
	 * @param fetchBatch fetch batch size
	 * @param sq1Out first output sequence
	 * @param sq2Out second output sequence
	 * @return operation result as a multiple values object
	 */
	public MultipleValuesHolder dbFetchRecords(DbCursorObject cursor, Item queryObject, int fetchBatch, Sequence sq1Out, Sequence sq2Out) throws SQLException, G2AccessException {
		ResultSet rs;
		Sequence columnNames;
		Sequence columnValues;
		int rowsProcessed = 0;
		int cursorPosition = 0;
		rs = performQueryOnCursor(cursor);
		columnNames = getColumnNames(rs);
		columnValues = getColumnValues(rs, fetchBatch);
		Symbol columnName;
		for (int i = 0; i < columnNames.size(); i++ ){
			columnName = (Symbol)columnNames.get(i);
			if (sq1Out.contains(columnName)) {
				Object column;
				try {
					column = queryObject.getPropertyValue(columnName);
					if (column instanceof com.gensym.classes.G2List) {
						Sequence s1 = (Sequence)columnValues.get(i);
						Sequence s2 = ((com.gensym.classes.G2List)column).getG2ListSequence();
						s2.addAll(s1);
						((com.gensym.classes.G2List)column).setG2ListSequence(s2);
					} else {
						queryObject.setPropertyValue(columnName, 
								((Sequence)columnValues.get(i)).lastElement());
					}
				} catch (NoSuchAttributeException e) {
					logger.warning(WarningMessage.NO_SUCH_ATTRIBUTE + columnName);
				}
			}
		}
		if (columnValues.get(0) != null) {
			rowsProcessed = ((Sequence)columnValues.get(0)).size();
		}
		cursorPosition = rs.getRow();
		if (cursorPosition == 0) {//TODO: JDBC returns 0 if the end is reached but odbc returns last row number 
			return MultipleValuesFactory.create5(StatusSymbol.EOCURSOR, 0, "", rowsProcessed, cursorPosition);
		} else {
			return MultipleValuesFactory.create5(StatusSymbol.SUCCESS, 0, "", rowsProcessed, cursorPosition);
		}
	}
	
	/**
	 * Returns data associated with a database cursor to G2 in a query item
	 * @param cursor Cursor to start fetching from
	 * @param returnFormat one of ARRAYS or LISTS symbols
	 * @param fetchBatch fetch batch size
	 * @return operation result as a multiple values object
	 */
	public MultipleValuesHolder dbFetchQueryItem(DbCursorObject cursor, int returnFormat, int fetchBatch) throws G2AccessException, G2StubCreationException, SQLException {
		ResultSet rs;
		Sequence columnNames;
		Sequence columnValues;
		int rowsProcessed = 0;
		int cursorPosition = 0;
		rs = performQueryOnCursor(cursor);
		DbQueryItem returnList;
		columnNames = getColumnNames(rs);
		columnValues = getColumnValues(rs, fetchBatch);
		if (returnFormat == ReturnUpdateControlValues.LIST) {
			returnList = (DbQueryItemList)
				G2StubResolver.createStubForG2Interface(DbQueryItemList.class);
			SymbolList dbColNames = (SymbolList)
				G2StubResolver.createStubForG2Interface(SymbolList.class);
			ItemList dbColValues = (ItemList)
				G2StubResolver.createStubForG2Interface(ItemList.class); 
				dbColNames.setG2ListSequence(columnNames);
			Sequence resColumnValues = new Sequence();
			for (int i = 0; i < columnValues.size(); i++) {
				TextListImpl colValuesList = new TextListImpl();
				colValuesList.setG2ListSequence((Sequence)columnValues.get(i));
				resColumnValues.add(colValuesList); //TODO: Need to check type converting in G2
			}
			dbColValues.setG2ListSequence(resColumnValues);
			((DbQueryItemList)returnList).setDbColNames(dbColNames);
			((DbQueryItemList)returnList).setDbColValues(dbColValues);
			} else if (returnFormat == ReturnUpdateControlValues.ARRAY) { 
				returnList = (DbQueryItemArray)
					G2StubResolver.createStubForG2Interface(DbQueryItemArray.class);
				SymbolArray dbColNames = (SymbolArray)
					G2StubResolver.createStubForG2Interface(SymbolArray.class);
				ItemArray dbColValues = (ItemArray)
					G2StubResolver.createStubForG2Interface(ItemArray.class); 

				dbColNames.setG2ArraySequence(columnNames);
				
				Sequence resColumnValues = new Sequence();
				for (int i = 0; i < columnValues.size(); i++) {
					TextListImpl colValuesList = new TextListImpl();
					colValuesList.setG2ListSequence((Sequence)columnValues.get(i));
					resColumnValues.add(colValuesList);//TODO: Need to check type converting in G2
				}
				dbColValues.setG2ArraySequence(resColumnValues);
				
				((DbQueryItemArray)returnList).setDbColNames(dbColNames);
				((DbQueryItemArray)returnList).setDbColValues(dbColValues);
			} else {
				logger.severe(ErrorMessage.WRONG_RETURN_TYPE);
				return MultipleValuesFactory.create6(null, StatusSymbol.ERROR, 0, ErrorMessage.WRONG_RETURN_TYPE, rowsProcessed, cursorPosition);
			}
			if (columnValues.get(0) != null) {
				rowsProcessed = ((Sequence)columnValues.get(0)).size();
			}
			cursorPosition = rs.getRow();
			if (cursorPosition == 0) {
				return MultipleValuesFactory.create6(returnList, StatusSymbol.EOCURSOR, 0, "", rowsProcessed, cursorPosition);
			} else {
				return MultipleValuesFactory.create6(returnList, StatusSymbol.SUCCESS, 0, "", rowsProcessed, cursorPosition);
			}
	}
	/**
	 * Returns data associated with a database cursor to an existing query item in G2.
     * The data within the query item may be either replaced or appended
	 * @param cursor database cursor to start fetching from
	 * @param queryItem query item to update
	 * @param updateType one of the REPLACE or APPEND symbols
	 * @param rcdsToUpdate maximum number of records to be updated
	 * @return operation result as a multiple values object
	 */
	public MultipleValuesHolder dbUpdateQueryItem(DbCursorObject cursor, DbQueryItem queryItem, int updateType, int rcdsToUpdate) throws G2StubCreationException, SQLException, G2AccessException {
		MultipleValuesHolder status = null;
			if (queryItem instanceof DbQueryItemList) {
				status =  dbFetchQueryItem(cursor, ReturnUpdateControlValues.LIST, rcdsToUpdate);
				DbQueryItemList qil = (DbQueryItemList)status.getFirst();
				SymbolList colNames = (SymbolList)qil.getDbColNames();
				ItemList colValues = (ItemList)qil.getDbColValues();
				
				DbQueryItemList qilRet = (DbQueryItemList)queryItem;
				SymbolList dbColNames = (SymbolList)qilRet.getDbColNames();
				ItemList dbColValues = (ItemList)qilRet.getDbColValues();
				
				if (updateType == ReturnUpdateControlValues.RELPACE) {
					dbColNames.setG2ListSequence(colNames.getG2ListSequence());
					dbColValues.setG2ListSequence(colValues.getG2ListSequence());
				} 
				if (updateType == ReturnUpdateControlValues.APPEND) {
					dbColNames.getG2ListSequence().concatenate(colNames.getG2ListSequence());
					dbColValues.getG2ListSequence().concatenate(colValues.getG2ListSequence());
				}
			}
			if (queryItem instanceof DbQueryItemArray) {
				status =  dbFetchQueryItem(cursor, ReturnUpdateControlValues.ARRAY, rcdsToUpdate);
				DbQueryItemArray qil = (DbQueryItemArray)status.getFirst();
				SymbolArray colNames = (SymbolArray)qil.getDbColNames();
				ItemArray colValues = (ItemArray)qil.getDbColValues();
				
				DbQueryItemArray qilRet = (DbQueryItemArray)queryItem;
				SymbolArray dbColNames = (SymbolArray)qilRet.getDbColNames();
				ItemArray dbColValues = (ItemArray)qilRet.getDbColValues();
				
				if (updateType == ReturnUpdateControlValues.RELPACE) {
					dbColNames.setG2ArraySequence(colNames.getG2ArraySequence());
					dbColValues.setG2ArraySequence(colValues.getG2ArraySequence());
				} 
				if (updateType == ReturnUpdateControlValues.APPEND) {
					dbColNames.getG2ArraySequence().concatenate(colNames.getG2ArraySequence());
					dbColValues.getG2ArraySequence().concatenate(colValues.getG2ArraySequence());
				}
			}
		if (status != null) {
			status.removeFirst();
			return status;
		} else {
			return MultipleValuesFactory.create5(StatusSymbol.ERROR, 0, ErrorMessage.UPDATE_QUERY_ITEM_FAILED, 0, 0);
		}
	}
	/**
	 * Performs a query and returns the results within a structure where each element of
     * the structure is a name/sequence pair containing one column of database data
	 * @param cursor database cursor to start fetching from
	 * @param fetchBatch maximum number of records to fetch
	 * @return operation result as a multiple values object
	 */
	public MultipleValuesHolder dbFetchStructure(DbCursorObject cursor, int fetchBatch) throws SQLException, G2AccessException {
		ResultSet rs;
		Sequence columnNames;
		Sequence columnValues;
		int rowsProcessed = 0;
		int cursorPosition = 0;
		rs = performQueryOnCursor(cursor);
		columnNames = getColumnNames(rs);
		columnValues = getColumnValues(rs, fetchBatch);
		Symbol columnName;
		Structure returnStruc = new Structure();
		for (int i = 0; i < columnNames.size(); i++) {
			columnName = (Symbol)columnNames.get(i);
			returnStruc.setAttributeValue(columnName, columnValues.get(i));
		}	
		if (columnValues.get(0) != null) {
			rowsProcessed = ((Sequence)columnValues.get(0)).size();
		}
		cursorPosition = rs.getRow();
		if (cursorPosition == 0) {
			return MultipleValuesFactory.create6(returnStruc, StatusSymbol.EOCURSOR, 0, "", rowsProcessed, cursorPosition);
		} else {
			return MultipleValuesFactory.create6(returnStruc, StatusSymbol.SUCCESS, 0, "", rowsProcessed, cursorPosition);
		}
	}
	/**
	 * Fetches  a copy of user-defined object 
	 * @param cursor Cursor position for fetch start
	 * @param mo user-defined object
	 * @param fetchBatch fetch batch size
	 * @param sq1Out first output sequence
	 * @param sq2Out second output sequence
	 * @return operation result as a multiple values object
	 */
	public MultipleValuesHolder dbFetchObjectCopy(DbCursorObject cursor, Item item, int fetchBatch, Sequence sq1Out, Sequence sq2Out) throws G2AccessException, SQLException {
		ResultSet rs;
		Sequence columnNames;
		Sequence rowValues;
		int rowsProcessed = 0;
		int cursorPosition = 0;
		rs = performQueryOnCursor(cursor);
		columnNames = getColumnNames(rs);
		rowValues = getRowValues(rs, fetchBatch);
		Symbol columnName;
		if (rowValues.firstElement() != null) {
			rowsProcessed = rowValues.capacity();
			Sequence lastRow = (Sequence)rowValues.lastElement();
			for (int i = 0; i < columnNames.size(); i++ ){
				columnName = (Symbol)columnNames.get(i);
				if (sq1Out.contains(columnName)) {
					item.setPropertyValue(columnName, lastRow.get(i));
				}
			}
		}
		cursorPosition = rs.getRow();
		if (cursorPosition == 0) {
			return MultipleValuesFactory.create6(item, StatusSymbol.EOCURSOR, 0, "", rowsProcessed, cursorPosition);
		} else {
			return MultipleValuesFactory.create6(item, StatusSymbol.SUCCESS, 0, "", rowsProcessed, cursorPosition);
		}
	}
	/**
	 * Fetches  a copy of user-defined object as list
	 * @param cursor Cursor position for fetch start
	 * @param mo user-defined object
	 * @param fetchBatch fetch batch size
	 * @param sq1Out first output sequence
	 * @param sq2Out second output sequence
	 * @return operation result as a multiple values object
	 */
	public MultipleValuesHolder dbFetchObjectList(DbCursorObject cursor, Item mo, int fetchBatch, Sequence sq1Out, Sequence sq2Out) throws G2AccessException, SQLException {
		ResultSet rs;
		Sequence columnNames;
		Sequence rowValues;
		int rowsProcessed = 0;
		int cursorPosition = 0;
		rs = performQueryOnCursor(cursor);
		columnNames = getColumnNames(rs);
		rowValues = getRowValues(rs, fetchBatch);
		Symbol columnName;
	
		ItemList itemList = (ItemList)application.createG2Item(Symbol.intern("ITEM-LIST"));
		Sequence itemSeq = new Sequence();
		for (int i = 0; i < rowValues.size(); i++ ){
			Item item = (Item)application.createG2Item(mo.getG2ClassName());
			for (int j = 0; j < columnNames.size(); j++) {
				columnName = (Symbol)columnNames.get(j);
				if (sq1Out.contains(columnName)) {
					item.setPropertyValue(columnName,
						((Sequence)rowValues.get(i)).get(j));
				}
			}
			itemSeq.add(item);
		}
		itemList.setG2ListSequence(itemSeq);
		rowsProcessed = rowValues.size();
		cursorPosition = rs.getRow();
		if (cursorPosition == 0) {
			return MultipleValuesFactory.create6(itemList, StatusSymbol.EOCURSOR, 0, "", rowsProcessed, cursorPosition);
		} else {
			return MultipleValuesFactory.create6(itemList, StatusSymbol.SUCCESS, 0, "", rowsProcessed, cursorPosition);
		}
	}
	/**
	 * Fetches values and stores them into user-defined object
	 * @param cursor Cursor to start fetching from
	 * @param queryObject user-defined object
	 * @param controlValue Control Value
	 * @param fetchBatch fetch batch size
	 * @param sq1Out first output sequence
	 * @param sq2Out second output sequence
	 * @return operation result as a multiple values object
	 */
	public MultipleValuesHolder dbFetchUpdateObject(DbCursorObject cursor, Item queryObject, int controlValue, int fetchBatch, Sequence sq1Out, Sequence sq2Out) throws SQLException, G2AccessException {
		ResultSet rs;
		Sequence columnNames;
		Sequence columnValues;
		int rowsProcessed = 0;
		int cursorPosition = 0;
		rs = performQueryOnCursor(cursor);
		columnNames = getColumnNames(rs);
		columnValues = getColumnValues(rs, fetchBatch);
		Symbol columnName;
		for (int i = 0; i < columnNames.size(); i++ ){
			columnName = (Symbol)columnNames.get(i);
			if (sq1Out.contains(columnName)) {
				Object column;
				try {
					column = queryObject.getPropertyValue(columnName);
					if (ReturnUpdateControlValues.RELPACE == controlValue){
						if (column instanceof com.gensym.classes.G2List) {
							((G2List)column).setG2ListSequence((Sequence)columnValues.get(i));
						} else if (column instanceof com.gensym.classes.G2Array){
							((G2Array)column).setG2ArraySequence((Sequence)columnValues.get(i));
						} else {							
							queryObject.setPropertyValue(columnName, 
									((Sequence)columnValues.get(i)).lastElement());
						}
					}
					if (ReturnUpdateControlValues.APPEND == controlValue){
						if (column instanceof com.gensym.classes.G2List) {
							((G2List)column).getG2ListSequence().
								addAll((Sequence)columnValues.get(i));
						} else 	if (column instanceof com.gensym.classes.G2Array){
							((G2Array)column).getG2ArraySequence().
								addAll((Sequence)columnValues.get(i));
						}
					}
				} catch (NoSuchAttributeException e) {
					logger.warning(WarningMessage.NO_SUCH_ATTRIBUTE + columnName);
				}
			}
		}
		if (columnValues.get(0) != null) {
			rowsProcessed = ((Sequence)columnValues.get(0)).size();
		}
		cursorPosition = rs.getRow();
		if (cursorPosition == 0) {
			return MultipleValuesFactory.create5(StatusSymbol.EOCURSOR, 0, "", rowsProcessed, cursorPosition);
		} else {
			return MultipleValuesFactory.create5(StatusSymbol.SUCCESS, 0, "", rowsProcessed, cursorPosition);
		}
	}
	/**
	 * Binds variables to the given PreparedStatement
	 * @param ps PreparedStatement to bind variables to
	 * @param tl TextList with binding values
	 * @throws G2AccessException when accessing G2 Sequence fails
	 * @throws SQLException when binding statement fails
	 */
	private void bindVariables(PreparedStatement ps, TextList tl) throws G2AccessException, SQLException {
		Enumeration e = tl.getG2ListSequence().elements();
		int maxBindVars = processParameters.getMaxBindVars();
		int i = 1;
		while (e.hasMoreElements()) {
			Object obj = e.nextElement();
			if (obj.equals(nullBindRepalcement)) {
				obj = null;
			}
			if (obj instanceof String) {
				obj = dbCharset.convertToThisCharset((String) obj);
			}
			if (maxBindVars != 0 && i >= maxBindVars) {
				logger.warning(WarningMessage.BIND_VARS_MAX_REACHED);
				break;
			}
			ps.setObject(i++, obj);
		}
	}
}