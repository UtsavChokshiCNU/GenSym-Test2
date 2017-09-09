package core;

import java.util.Random;

import config.BridgeParameters;
import config.ProcessParameters;
import exception.*;
import core.BridgeCore;

import com.gensym.classes.Item;
import com.gensym.classes.ItemArray;
import com.gensym.classes.ItemArrayImpl;
import com.gensym.classes.ItemImpl;
import com.gensym.classes.ItemList;
import com.gensym.classes.ItemListImpl;
import com.gensym.classes.SymbolArray;
import com.gensym.classes.SymbolArrayImpl;
import com.gensym.classes.SymbolList;
import com.gensym.classes.SymbolListImpl;
import com.gensym.classes.TextList;
import com.gensym.classes.TextListImpl;
import com.gensym.classes.modules.g2database.DbCursorObjectImpl;
import com.gensym.classes.modules.g2database.DbQueryItemArray;
import com.gensym.classes.modules.g2database.DbQueryItemArrayImpl;
import com.gensym.classes.modules.g2database.DbQueryItemListImpl;
import com.gensym.classes.modules.g2database.DbSqlObject;
import com.gensym.classes.modules.g2database.DbSqlObjectImpl;
import com.gensym.util.NoSuchAttributeException;
import com.gensym.util.Symbol;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.MultipleValuesHolder;
import com.gensym.util.Sequence;

import type.GDBControlValue;
import type.ReturnUpdateControlValues;
import type.StatusSymbol;
import static org.junit.Assert.*;
import static org.easymock.classextension.EasyMock.*;


/**
 * This class contains bridge core tests
 * @author SoftServe
 *
 */
public class BridgeCoreTest {
	
	private static final String userName = "gensym";
	private static final String password = "gensym";
	private static final String conStr = 
		"jdbc:postgresql://localhost:5432/g2jdbctest";
	private BridgeCore bc = null;
	private MultipleValuesHolder status;
	private G2JDBCBridge application;
	
	@org.junit.Before
	public void connect() {
		BridgeParameters bp = new BridgeParameters();
		ProcessParameters pp = new ProcessParameters();
		pp.setDisableConsoleOut(true);
		pp.setDisableLogTimestamp(true);
		bp.setDriver("org.postgresql.Driver");
		application = createMock(G2JDBCBridge.class);
		bc = new BridgeCore(bp, pp, application);
		bc.dbConfiguration(0, "", "tlog.log, ALL", false, 11, false, "", 0, "", 0, 0);
		status = bc.dbConnect(userName, password, conStr);
		assertEquals(StatusSymbol.SUCCESS, status.getFirst());
	}
	
	@org.junit.After
	public void disconnect() {
		status = bc.dbDisconnect();
		assertEquals(StatusSymbol.SUCCESS, status.getFirst());
	}
	
	@org.junit.Test
	public void testdbPing() {
		status = bc.dbPing();
		assertEquals(status.get(0), StatusSymbol.SUCCESS);
	}
	
	@org.junit.Test
	public void testImmediateExecution() {
		status = bc.dbExecuteImmediate("CREATE TABLE T1 (F1 char(20))", true);
		assertEquals(StatusSymbol.SUCCESS, status.getFirst());
		status = bc.dbExecuteImmediate("DROP TABLE T1", true);
		assertEquals(StatusSymbol.SUCCESS, status.getFirst());
	}
	
	@org.junit.Test
	public void testdbCommit() {
		status = bc.dbExecuteImmediate("CREATE TABLE T2 (F2 char(20))", false);
		assertEquals(StatusSymbol.SUCCESS, status.getFirst());
		status = bc.dbCommit();
		assertEquals(StatusSymbol.SUCCESS, status.getFirst());	
		status = bc.dbExecuteImmediate("DROP TABLE T2", true);
		assertEquals(StatusSymbol.SUCCESS, status.getFirst());
	}
	
	@org.junit.Test
	public void testdbExecStoredProc() {
		status = bc.dbExecuteImmediate("DROP TABLE AUTOTABLE", true);
		status = bc.dbExecuteImmediate("create function add_table() returns void as" +
				" 'create table autotable (key integer)' language sql", true);
		assertEquals(StatusSymbol.SUCCESS, status.getFirst());
		status = bc.dbExecStoredProc("add_table()", "EXEC");	
		assertEquals(StatusSymbol.SUCCESS, status.getFirst());
		status = bc.dbExecuteImmediate("DROP TABLE AUTOTABLE", true);
		assertEquals(StatusSymbol.SUCCESS, status.getFirst());
		status = bc.dbExecuteImmediate("DROP FUNCTION add_table()", true);
		assertEquals(StatusSymbol.SUCCESS, status.getFirst());
	}

	private void createTableForTest() {
		bc.dbExecuteImmediate("create table test (user_id int, user_name char(20), user_tmp char(50))", true);
	}
	
	private void setTestTableData(int size) {
		Random r = new Random();
		int id;
		String user_name;
		String user_tmp;
		for (int i = 1; i <= size; i++) {
			id = r.nextInt();
			user_name = Long.toString(Math.abs(r.nextLong()), 36);
			user_tmp = Long.toString(Math.abs(r.nextLong()), 36);
			String sql = "INSERT INTO test(user_id, user_name, user_tmp) VALUES (" +
				id + ",'" +
				user_name +"','" + 
				user_tmp + "')";
			status = bc.dbExecuteImmediate(sql, true);
		}
	}
	
	private void dropTestTable() {
		status = bc.dbExecuteImmediate("drop table test", true);
	}
	
	@org.junit.Test
	public void testdbDefineSetCursor() throws G2AccessException {
		DbCursorObjectImpl cursor = new DbCursorObjectImpl();
		TextListImpl bindVars = new TextListImpl();
		Sequence seq = new Sequence();
		bindVars.setG2ListSequence(seq);
		status = bc.dbSetCursor(cursor, "select * from autotable", GDBControlValue.GDB_INIT, bindVars);
		assertEquals(StatusSymbol.SUCCESS, status.getFirst());
		status = bc.dbSetCursor(cursor, "select * from autotable", GDBControlValue.GDB_UPDATE, bindVars);
		assertEquals(StatusSymbol.SUCCESS, status.getFirst());
	}

	@org.junit.Test
	public void testdbFetchRecords() throws G2AccessException, NoSuchAttributeException {
		Sequence s1 = new Sequence();
		s1.add("s1");
		Sequence s2 = new Sequence();
		s2.add("s2");
		s1.addAll(s2);
		System.out.println(s1);
		dropTestTable();
		createTableForTest();
		setTestTableData(100);
		DbCursorObjectImpl cursor = new DbCursorObjectImpl();
		TextListImpl bindVars = new TextListImpl();
		Sequence seq = new Sequence();
		bindVars.setG2ListSequence(seq);
		status = bc.dbSetCursor(cursor, "select * from test", GDBControlValue.GDB_INIT, bindVars);
		Sequence sq1Out = new Sequence();
		Symbol user = Symbol.intern("USER_NAME");
		sq1Out.add(user);
		Sequence sq2Out = new Sequence();
		sq2Out.addBooleanElement(false);
		ItemImpl mo = new ItemImpl();
		ItemListImpl itemList = new ItemListImpl();
		itemList.setG2ListSequence(new Sequence());
		mo.setPropertyValue(user, itemList);
		status = bc.dbFetchRecords(cursor, mo, 100, sq1Out, sq2Out);
		assertEquals(StatusSymbol.SUCCESS, status.getFirst());
		mo.setPropertyValue(user, "");
		status = bc.dbFetchRecords(cursor, mo, 0, sq1Out, sq2Out);
		assertEquals(StatusSymbol.EOCURSOR, status.getFirst());
		dropTestTable();
	}
	
	@org.junit.Test
	public void testdbFetchStructure() throws G2AccessException {
		dropTestTable();
		createTableForTest();
		setTestTableData(100);
		DbCursorObjectImpl cursor = new DbCursorObjectImpl();
		TextListImpl bindVars = new TextListImpl();
		Sequence seq = new Sequence();
		bindVars.setG2ListSequence(seq);
		status = bc.dbSetCursor(cursor, "select * from test", GDBControlValue.GDB_INIT, bindVars);
		status = bc.dbFetchStructure(cursor, 100);
		assertEquals(StatusSymbol.SUCCESS, status.get(1));
		status = bc.dbFetchStructure(cursor, 0);
		assertEquals(StatusSymbol.EOCURSOR, status.get(1));
		dropTestTable();
	}
	
	
	@org.junit.Test
	public void testdbFetchQueryItem() throws G2AccessException, NoSuchAttributeException {
		dropTestTable();
		createTableForTest();
		setTestTableData(100);
		DbCursorObjectImpl cursor = new DbCursorObjectImpl();
		TextListImpl bindVars = new TextListImpl();
		Sequence seq = new Sequence();
		bindVars.setG2ListSequence(seq);
		status = bc.dbSetCursor(cursor, "select * from test", GDBControlValue.GDB_INIT, bindVars);
		status = bc.dbFetchQueryItem(cursor, 1, 99);
		assertEquals(StatusSymbol.SUCCESS, status.get(1));
		status = bc.dbFetchQueryItem(cursor, ReturnUpdateControlValues.LIST, 99);
		assertEquals(StatusSymbol.SUCCESS, status.get(1));
		status = bc.dbFetchQueryItem(cursor, ReturnUpdateControlValues.ARRAY, 0);
		assertEquals(StatusSymbol.EOCURSOR, status.get(1));
		status = bc.dbFetchQueryItem(cursor, 3, 99);
		assertEquals(StatusSymbol.ERROR, status.get(1));
	}	
	
	
	@org.junit.Test
	public void testdbUpdateQueryItemAsList() throws G2AccessException, NoSuchAttributeException {
		dropTestTable();
		createTableForTest();
		setTestTableData(100);
		DbCursorObjectImpl cursor = new DbCursorObjectImpl();
		TextListImpl bindVars = new TextListImpl();
		Sequence seq = new Sequence();
		bindVars.setG2ListSequence(seq);
		status = bc.dbSetCursor(cursor, "select * from test", GDBControlValue.GDB_INIT, bindVars);
		DbQueryItemListImpl queryItem = new DbQueryItemListImpl();
		SymbolList dbColNames = new SymbolListImpl();
		ItemList dbColValues = new ItemListImpl();
		dbColNames.setG2ListSequence(new Sequence());
		dbColValues.setG2ListSequence(new Sequence());
		queryItem.setPropertyValue(Symbol.intern("DB-COL-NAMES"), dbColNames);
		queryItem.setPropertyValue(Symbol.intern("DB-COL-VALUES"), dbColValues);
		status = bc.dbUpdateQueryItem(cursor, queryItem, 1, 99);
		assertEquals(StatusSymbol.SUCCESS, status.getFirst());
		status = bc.dbUpdateQueryItem(cursor, queryItem, 2, 99);
		assertEquals(StatusSymbol.SUCCESS, status.getFirst());
	}	
	
	@org.junit.Test
	public void testdbUpdateQueryItemAsArray() throws G2AccessException, NoSuchAttributeException {
		dropTestTable();
		createTableForTest();
		setTestTableData(100);
		DbCursorObjectImpl cursor = new DbCursorObjectImpl();
		TextListImpl bindVars = new TextListImpl();
		Sequence seq = new Sequence();
		bindVars.setG2ListSequence(seq);
		status = bc.dbSetCursor(cursor, "select * from test", GDBControlValue.GDB_INIT, bindVars);
		DbQueryItemArray queryItem = new DbQueryItemArrayImpl();
		SymbolArray dbColNames = new SymbolArrayImpl();
		ItemArray dbColValues = new ItemArrayImpl();
		dbColNames.setG2ArraySequence(new Sequence());
		dbColValues.setG2ArraySequence(new Sequence());
		queryItem.setPropertyValue(Symbol.intern("DB-COL-NAMES"), dbColNames);
		queryItem.setPropertyValue(Symbol.intern("DB-COL-VALUES"), dbColValues);
		status = bc.dbUpdateQueryItem(cursor, queryItem, 1, 99);
		assertEquals(StatusSymbol.SUCCESS, status.getFirst());
		status = bc.dbUpdateQueryItem(cursor, queryItem, 2, 99);
		assertEquals(StatusSymbol.SUCCESS, status.getFirst());
	}	

	
	@org.junit.Test
	public void testdbFetchObjectCopy() throws G2AccessException, NoSuchAttributeException {
		DbCursorObjectImpl cursor = new DbCursorObjectImpl();
		cursor.setDbCursorPosition(0);
		TextListImpl bindVars = new TextListImpl();
		Sequence seq = new Sequence();
		bindVars.setG2ListSequence(seq);
		status = bc.dbSetCursor(cursor, "select * from test", GDBControlValue.GDB_INIT, bindVars);
		Sequence sq1Out = new Sequence();
		Symbol user = Symbol.intern("user_name".toUpperCase());
		sq1Out.add(user);
		Sequence sq2Out = new Sequence();
		sq2Out.addBooleanElement(false);
		ItemImpl mo = new ItemImpl();
		mo.setPropertyValue(user, null);
		status = bc.dbFetchObjectCopy(cursor, mo, 10, sq1Out, sq2Out);
		assertEquals(StatusSymbol.SUCCESS, status.get(1));
		status = bc.dbFetchObjectCopy(cursor, mo, 0, sq1Out, sq2Out);
		assertEquals(StatusSymbol.EOCURSOR, status.get(1));
	}
	
	
	@org.junit.Test
	public void testdbFetchObjectlist() throws G2AccessException, NoSuchAttributeException {
		DbCursorObjectImpl cursor = new DbCursorObjectImpl();
		cursor.setDbCursorPosition(0);
		TextListImpl bindVars = new TextListImpl();
		Sequence seq = new Sequence();
		bindVars.setG2ListSequence(seq);
		status = bc.dbSetCursor(cursor, "select * from test", GDBControlValue.GDB_INIT, bindVars);
		Sequence sq1Out = new Sequence();
		Symbol user = Symbol.intern("user_name".toUpperCase());
		Symbol itemClass = Symbol.intern("ITEM");
		sq1Out.add(user);
		Sequence sq2Out = new Sequence();
		sq2Out.addBooleanElement(false);
		Item item = new ItemImpl();
		Item itemList = new ItemListImpl();
		Item mo = createMock(Item.class);
		expect(application.createG2Item(Symbol.intern("ITEM-LIST"))).andReturn(itemList);
		expect(mo.getG2ClassName()).andReturn(itemClass);
		expect(application.createG2Item(itemClass)).andReturn(item);
		replay(application);
		replay(mo);
		status = bc.dbFetchObjectList(cursor, mo, 1, sq1Out, sq2Out);
		assertEquals(StatusSymbol.SUCCESS, status.get(1));
	}
	
	@org.junit.Test
	public void testdbFetchUpdateObject() throws G2AccessException, NoSuchAttributeException {
		DbCursorObjectImpl cursor = new DbCursorObjectImpl();
		cursor.setDbCursorPosition(0);
		TextListImpl bindVars = new TextListImpl();
		Sequence seq = new Sequence();
		bindVars.setG2ListSequence(seq);
		status = bc.dbSetCursor(cursor, "select * from test", GDBControlValue.GDB_INIT, bindVars);
		Sequence sq1Out = new Sequence();
		Symbol user = Symbol.intern("user_name".toUpperCase());
		sq1Out.add(user);
		Sequence sq2Out = new Sequence();
		sq2Out.addBooleanElement(false);
		ItemImpl mo = new ItemImpl();
		ItemListImpl itemList = new ItemListImpl();
		itemList.setG2ListSequence(sq2Out);
		mo.setPropertyValue(user, itemList);
		status = bc.dbFetchUpdateObject(cursor, mo, ReturnUpdateControlValues.RELPACE, 10, sq1Out, sq2Out);
		assertEquals(StatusSymbol.SUCCESS, status.getFirst());
		status = bc.dbFetchUpdateObject(cursor, mo, ReturnUpdateControlValues.APPEND, 10, sq1Out, sq2Out);
		assertEquals(StatusSymbol.SUCCESS, status.getFirst());
		ItemArray itemArray = new ItemArrayImpl();
		itemArray.setG2ArraySequence(sq2Out);
		mo.setPropertyValue(user, itemArray);
		status = bc.dbFetchUpdateObject(cursor, mo, ReturnUpdateControlValues.RELPACE, 0, sq1Out, sq2Out);
		assertEquals(StatusSymbol.EOCURSOR, status.getFirst());
		status = bc.dbFetchUpdateObject(cursor, mo, ReturnUpdateControlValues.APPEND, 10, sq1Out, sq2Out);
		assertEquals(StatusSymbol.SUCCESS, status.getFirst());
		mo.setPropertyValue(user, "");
		status = bc.dbFetchUpdateObject(cursor, mo, ReturnUpdateControlValues.RELPACE, 10, sq1Out, sq2Out);
		assertEquals(StatusSymbol.SUCCESS, status.getFirst());
	}
	
	@org.junit.Test
	public void testdbExecStoredProcRetVal() {
		MultipleValuesHolder mvh =
			bc.dbExecuteImmediate("CREATE FUNCTION RET_VAL(x integer) " +
					"RETURNS INTEGER AS $$ begin return x; end $$ LANGUAGE plpgsql;", true);
		assertEquals(StatusSymbol.SUCCESS, mvh.getFirst());
		mvh =  bc.dbExecStoredProcRet("ret_val", "44");
		assertEquals(StatusSymbol.SUCCESS, mvh.get(1));
		assertEquals("44", mvh.getFirst());
		mvh = bc.dbExecuteImmediate("drop function ret_val(integer)", true);
		assertEquals(StatusSymbol.SUCCESS, mvh.getFirst());
	}
	
	@org.junit.Test
	public void testdbExecSQL() throws G2AccessException {
		DbSqlObject dbo = new DbSqlObjectImpl();
		TextList tl = new TextListImpl();
		Sequence s = new Sequence();
		s.add(453);
		s.add(7265);
		tl.setG2ListSequence(s);
		MultipleValuesHolder mvh = 
			bc.dbExecuteImmediate("create table testtable (key integer, value integer)", true);
		mvh = bc.dbSetDynamicExec(dbo,
				"INSERT INTO testtable (key,value) values (:a,:b);", GDBControlValue.GDB_INIT, tl, false);
		bc.dbSetDynamicExec(dbo, "", GDBControlValue.GDB_UPDATE, tl, false);
		assertEquals(StatusSymbol.SUCCESS, mvh.getFirst());
		mvh = bc.dbSetDynamicExec(dbo, "", GDBControlValue.GDB_EXECUTE, tl, true);
		bc.dbRefreshCursor(null);
		mvh = bc.dbSetDynamicExec(dbo, "", GDBControlValue.GDB_EXECUTE, tl, false);
		mvh = bc.dbSetDynamicExec(dbo, "", GDBControlValue.GDB_EXECUTE, tl, true);
		assertEquals(StatusSymbol.SUCCESS, mvh.getFirst());
		assertEquals(1, mvh.get(4));
		mvh = bc.dbRollback();
		assertEquals(StatusSymbol.SUCCESS, mvh.getFirst());	
		tl.setG2ListSequence(new Sequence());
		mvh = bc.dbSetDynamicExec(dbo,
				"SELECT key, value FROM TESTTABLE", GDBControlValue.GDB_INIT, tl, false);
		assertEquals(StatusSymbol.SUCCESS, mvh.getFirst());
		mvh = bc.dbSetDynamicExec(dbo, "", GDBControlValue.GDB_EXECUTE, new TextListImpl(), true);
		assertEquals(StatusSymbol.SUCCESS, mvh.getFirst());
		mvh = bc.dbExecuteImmediate("drop table testtable", true);
		assertEquals(StatusSymbol.SUCCESS, mvh.getFirst());
	}
	
	@org.junit.Test
	public void testdbSQLFunction() {
		dropTestTable();
		createTableForTest();
		setTestTableData(100);
		MultipleValuesHolder mvh = 
			bc.dbSQLFunction("SELECT COUNT(*) FROM TEST");
		assertEquals(StatusSymbol.SUCCESS, mvh.get(2));
		assertTrue(mvh.getFirst() != null);
		assertTrue(mvh.get(1) == null);
		dropTestTable();
	}

	@org.junit.Test 
	public void testSQLObjects() throws G2AccessException {
		DbSqlObject dbo = new DbSqlObjectImpl();
		TextList tl = new TextListImpl();
		Sequence s = new Sequence();
		s.add(45); 
		s.add(725);
		tl.setG2ListSequence(s);
		MultipleValuesHolder mvh = bc.dbSetDynamicExec(dbo,
				"INSERT INTO \"TESTTABLE\" (key,value) values (:k,:v)",
				GDBControlValue.GDB_INIT, tl, true);
		assertEquals(StatusSymbol.SUCCESS, mvh.getFirst());
		DbQueryItemArray queryItem = new DbQueryItemArrayImpl();
		queryItem.setPropertyValue(Symbol.intern("KEY"), 0);
		queryItem.setPropertyValue(Symbol.intern("VALUE"), "3");
		mvh = bc.dbExecSQLObj(dbo, "KEY,VALUE", GDBControlValue.GDB_UPDATE, queryItem, false);
		assertEquals(StatusSymbol.SUCCESS, mvh.getFirst());
	}
	
	@org.junit.Test
	public void dbLogfileTest() {
		MultipleValuesHolder mvh = bc.dbLogfile(Symbol.intern("CLOSE"), "", "");
		assertEquals(StatusSymbol.SUCCESS, mvh.getFirst());
		mvh = bc.dbLogfile(Symbol.intern("OPEN"), 
				"ALL, FATAL, ERROR, WARNING, WARN, INFO", "mynewlog.txt");
		assertEquals(StatusSymbol.SUCCESS, mvh.getFirst());
	}
	
	@org.junit.Test
	public void dbTestTriggers() {
		MultipleValuesHolder mvh = bc.dbGetTriggers();
		assertEquals(StatusSymbol.FATAL, mvh.get(2));
		mvh = bc.dbDisableAllTriggers();
		assertEquals(StatusSymbol.FATAL, mvh.getFirst());
		mvh = bc.dbSetTrigger(null, false);
		assertEquals(StatusSymbol.FATAL, mvh.getFirst());
		mvh = bc.dbSetTriggerObj(null, false);
		assertEquals(StatusSymbol.FATAL, mvh.getFirst());
	}
	
	@org.junit.Test
	public void testConsole() {
		Console.enable();
		Console.puts("Test");
		Console.putsWithDate("Another test");
		Console c = new Console();
		assertFalse(c == null);
	}
	
	//tests stubs and class default constructors to improve coverage
	@org.junit.Test
	public void testStubs() {
		ErrorMessage emsg = new ErrorMessage();
		assertFalse (emsg == null);
		InfoMessage imsg = new InfoMessage();
		assertFalse (imsg == null);
		WarningMessage wmsg = new WarningMessage();
		assertFalse (wmsg == null);
		InvalidCommandLineException icle = new InvalidCommandLineException();
		assertFalse(icle == null);
		MultipleValuesHolder mvh = bc.dbRedirectCallback();
		assertEquals(StatusSymbol.FATAL, mvh.getFirst());
		BridgeParameters bp = bc.getBridgeParameters();
		assertFalse(bp == null);
		bc.setBridgeParameters(bp);
	}
}
