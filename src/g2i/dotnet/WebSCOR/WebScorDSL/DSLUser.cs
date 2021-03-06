﻿//------------------------------------------------------------------------------
// <autogenerated>
//     This code was generated by a tool.
//     Runtime Version: 1.1.4322.2032
//
//     Changes to this file may cause incorrect behavior and will be lost if 
//     the code is regenerated.
// </autogenerated>
//------------------------------------------------------------------------------

namespace WebScorDSL {
    using System;
    using System.Data;
    using System.Xml;
    using System.Runtime.Serialization;
    
    
    [Serializable()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Diagnostics.DebuggerStepThrough()]
    [System.ComponentModel.ToolboxItem(true)]
    public class DSLUser : DataSet {
        
        private TUsersDataTable tableTUsers;
        
        public DSLUser() {
            this.InitClass();
            System.ComponentModel.CollectionChangeEventHandler schemaChangedHandler = new System.ComponentModel.CollectionChangeEventHandler(this.SchemaChanged);
            this.Tables.CollectionChanged += schemaChangedHandler;
            this.Relations.CollectionChanged += schemaChangedHandler;
        }
        
        protected DSLUser(SerializationInfo info, StreamingContext context) {
            string strSchema = ((string)(info.GetValue("XmlSchema", typeof(string))));
            if ((strSchema != null)) {
                DataSet ds = new DataSet();
                ds.ReadXmlSchema(new XmlTextReader(new System.IO.StringReader(strSchema)));
                if ((ds.Tables["TUsers"] != null)) {
                    this.Tables.Add(new TUsersDataTable(ds.Tables["TUsers"]));
                }
                this.DataSetName = ds.DataSetName;
                this.Prefix = ds.Prefix;
                this.Namespace = ds.Namespace;
                this.Locale = ds.Locale;
                this.CaseSensitive = ds.CaseSensitive;
                this.EnforceConstraints = ds.EnforceConstraints;
                this.Merge(ds, false, System.Data.MissingSchemaAction.Add);
                this.InitVars();
            }
            else {
                this.InitClass();
            }
            this.GetSerializationData(info, context);
            System.ComponentModel.CollectionChangeEventHandler schemaChangedHandler = new System.ComponentModel.CollectionChangeEventHandler(this.SchemaChanged);
            this.Tables.CollectionChanged += schemaChangedHandler;
            this.Relations.CollectionChanged += schemaChangedHandler;
        }
        
        [System.ComponentModel.Browsable(false)]
        [System.ComponentModel.DesignerSerializationVisibilityAttribute(System.ComponentModel.DesignerSerializationVisibility.Content)]
        public TUsersDataTable TUsers {
            get {
                return this.tableTUsers;
            }
        }
        
        public override DataSet Clone() {
            DSLUser cln = ((DSLUser)(base.Clone()));
            cln.InitVars();
            return cln;
        }
        
        protected override bool ShouldSerializeTables() {
            return false;
        }
        
        protected override bool ShouldSerializeRelations() {
            return false;
        }
        
        protected override void ReadXmlSerializable(XmlReader reader) {
            this.Reset();
            DataSet ds = new DataSet();
            ds.ReadXml(reader);
            if ((ds.Tables["TUsers"] != null)) {
                this.Tables.Add(new TUsersDataTable(ds.Tables["TUsers"]));
            }
            this.DataSetName = ds.DataSetName;
            this.Prefix = ds.Prefix;
            this.Namespace = ds.Namespace;
            this.Locale = ds.Locale;
            this.CaseSensitive = ds.CaseSensitive;
            this.EnforceConstraints = ds.EnforceConstraints;
            this.Merge(ds, false, System.Data.MissingSchemaAction.Add);
            this.InitVars();
        }
        
        protected override System.Xml.Schema.XmlSchema GetSchemaSerializable() {
            System.IO.MemoryStream stream = new System.IO.MemoryStream();
            this.WriteXmlSchema(new XmlTextWriter(stream, null));
            stream.Position = 0;
            return System.Xml.Schema.XmlSchema.Read(new XmlTextReader(stream), null);
        }
        
        internal void InitVars() {
            this.tableTUsers = ((TUsersDataTable)(this.Tables["TUsers"]));
            if ((this.tableTUsers != null)) {
                this.tableTUsers.InitVars();
            }
        }
        
        private void InitClass() {
            this.DataSetName = "DSLUser";
            this.Prefix = "";
            this.Namespace = "http://www.tempuri.org/DSLUser.xsd";
            this.Locale = new System.Globalization.CultureInfo("en-US");
            this.CaseSensitive = false;
            this.EnforceConstraints = true;
            this.tableTUsers = new TUsersDataTable();
            this.Tables.Add(this.tableTUsers);
        }
        
        private bool ShouldSerializeTUsers() {
            return false;
        }
        
        private void SchemaChanged(object sender, System.ComponentModel.CollectionChangeEventArgs e) {
            if ((e.Action == System.ComponentModel.CollectionChangeAction.Remove)) {
                this.InitVars();
            }
        }
        
        public delegate void TUsersRowChangeEventHandler(object sender, TUsersRowChangeEvent e);
        
        [System.Diagnostics.DebuggerStepThrough()]
        public class TUsersDataTable : DataTable, System.Collections.IEnumerable {
            
            private DataColumn columnuserId;
            
            private DataColumn columncoId;
            
            private DataColumn columnfirstName;
            
            private DataColumn columnlastName;
            
            private DataColumn columnuserName;
            
            private DataColumn columnpassword;
            
            private DataColumn columnanyServer;
            
            private DataColumn columninactive;
            
            private DataColumn columnuserRole;
            
            private DataColumn columnuserMode;
            
            internal TUsersDataTable() : 
                    base("TUsers") {
                this.InitClass();
            }
            
            internal TUsersDataTable(DataTable table) : 
                    base(table.TableName) {
                if ((table.CaseSensitive != table.DataSet.CaseSensitive)) {
                    this.CaseSensitive = table.CaseSensitive;
                }
                if ((table.Locale.ToString() != table.DataSet.Locale.ToString())) {
                    this.Locale = table.Locale;
                }
                if ((table.Namespace != table.DataSet.Namespace)) {
                    this.Namespace = table.Namespace;
                }
                this.Prefix = table.Prefix;
                this.MinimumCapacity = table.MinimumCapacity;
                this.DisplayExpression = table.DisplayExpression;
            }
            
            [System.ComponentModel.Browsable(false)]
            public int Count {
                get {
                    return this.Rows.Count;
                }
            }
            
            internal DataColumn userIdColumn {
                get {
                    return this.columnuserId;
                }
            }
            
            internal DataColumn coIdColumn {
                get {
                    return this.columncoId;
                }
            }
            
            internal DataColumn firstNameColumn {
                get {
                    return this.columnfirstName;
                }
            }
            
            internal DataColumn lastNameColumn {
                get {
                    return this.columnlastName;
                }
            }
            
            internal DataColumn userNameColumn {
                get {
                    return this.columnuserName;
                }
            }
            
            internal DataColumn passwordColumn {
                get {
                    return this.columnpassword;
                }
            }
            
            internal DataColumn anyServerColumn {
                get {
                    return this.columnanyServer;
                }
            }
            
            internal DataColumn inactiveColumn {
                get {
                    return this.columninactive;
                }
            }
            
            internal DataColumn userRoleColumn {
                get {
                    return this.columnuserRole;
                }
            }
            
            internal DataColumn userModeColumn {
                get {
                    return this.columnuserMode;
                }
            }
            
            public TUsersRow this[int index] {
                get {
                    return ((TUsersRow)(this.Rows[index]));
                }
            }
            
            public event TUsersRowChangeEventHandler TUsersRowChanged;
            
            public event TUsersRowChangeEventHandler TUsersRowChanging;
            
            public event TUsersRowChangeEventHandler TUsersRowDeleted;
            
            public event TUsersRowChangeEventHandler TUsersRowDeleting;
            
            public void AddTUsersRow(TUsersRow row) {
                this.Rows.Add(row);
            }
            
            public TUsersRow AddTUsersRow(int coId, string firstName, string lastName, string userName, string password, bool anyServer, bool inactive, int userRole, string userMode) {
                TUsersRow rowTUsersRow = ((TUsersRow)(this.NewRow()));
                rowTUsersRow.ItemArray = new object[] {
                        null,
                        coId,
                        firstName,
                        lastName,
                        userName,
                        password,
                        anyServer,
                        inactive,
                        userRole,
                        userMode};
                this.Rows.Add(rowTUsersRow);
                return rowTUsersRow;
            }
            
            public TUsersRow FindByuserId(int userId) {
                return ((TUsersRow)(this.Rows.Find(new object[] {
                            userId})));
            }
            
            public System.Collections.IEnumerator GetEnumerator() {
                return this.Rows.GetEnumerator();
            }
            
            public override DataTable Clone() {
                TUsersDataTable cln = ((TUsersDataTable)(base.Clone()));
                cln.InitVars();
                return cln;
            }
            
            protected override DataTable CreateInstance() {
                return new TUsersDataTable();
            }
            
            internal void InitVars() {
                this.columnuserId = this.Columns["userId"];
                this.columncoId = this.Columns["coId"];
                this.columnfirstName = this.Columns["firstName"];
                this.columnlastName = this.Columns["lastName"];
                this.columnuserName = this.Columns["userName"];
                this.columnpassword = this.Columns["password"];
                this.columnanyServer = this.Columns["anyServer"];
                this.columninactive = this.Columns["inactive"];
                this.columnuserRole = this.Columns["userRole"];
                this.columnuserMode = this.Columns["userMode"];
            }
            
            private void InitClass() {
                this.columnuserId = new DataColumn("userId", typeof(int), null, System.Data.MappingType.Element);
                this.Columns.Add(this.columnuserId);
                this.columncoId = new DataColumn("coId", typeof(int), null, System.Data.MappingType.Element);
                this.Columns.Add(this.columncoId);
                this.columnfirstName = new DataColumn("firstName", typeof(string), null, System.Data.MappingType.Element);
                this.Columns.Add(this.columnfirstName);
                this.columnlastName = new DataColumn("lastName", typeof(string), null, System.Data.MappingType.Element);
                this.Columns.Add(this.columnlastName);
                this.columnuserName = new DataColumn("userName", typeof(string), null, System.Data.MappingType.Element);
                this.Columns.Add(this.columnuserName);
                this.columnpassword = new DataColumn("password", typeof(string), null, System.Data.MappingType.Element);
                this.Columns.Add(this.columnpassword);
                this.columnanyServer = new DataColumn("anyServer", typeof(bool), null, System.Data.MappingType.Element);
                this.Columns.Add(this.columnanyServer);
                this.columninactive = new DataColumn("inactive", typeof(bool), null, System.Data.MappingType.Element);
                this.Columns.Add(this.columninactive);
                this.columnuserRole = new DataColumn("userRole", typeof(int), null, System.Data.MappingType.Element);
                this.Columns.Add(this.columnuserRole);
                this.columnuserMode = new DataColumn("userMode", typeof(string), null, System.Data.MappingType.Element);
                this.Columns.Add(this.columnuserMode);
                this.Constraints.Add(new UniqueConstraint("Constraint1", new DataColumn[] {
                                this.columnuserId}, true));
                this.columnuserId.AutoIncrement = true;
                this.columnuserId.AllowDBNull = false;
                this.columnuserId.ReadOnly = true;
                this.columnuserId.Unique = true;
                this.columncoId.AllowDBNull = false;
                this.columnfirstName.AllowDBNull = false;
                this.columnlastName.AllowDBNull = false;
                this.columnuserName.AllowDBNull = false;
                this.columnpassword.AllowDBNull = false;
                this.columnanyServer.AllowDBNull = false;
                this.columnanyServer.DefaultValue = true;
                this.columninactive.AllowDBNull = false;
                this.columninactive.DefaultValue = false;
                this.columnuserRole.AllowDBNull = false;
                this.columnuserMode.AllowDBNull = false;
            }
            
            public TUsersRow NewTUsersRow() {
                return ((TUsersRow)(this.NewRow()));
            }
            
            protected override DataRow NewRowFromBuilder(DataRowBuilder builder) {
                return new TUsersRow(builder);
            }
            
            protected override System.Type GetRowType() {
                return typeof(TUsersRow);
            }
            
            protected override void OnRowChanged(DataRowChangeEventArgs e) {
                base.OnRowChanged(e);
                if ((this.TUsersRowChanged != null)) {
                    this.TUsersRowChanged(this, new TUsersRowChangeEvent(((TUsersRow)(e.Row)), e.Action));
                }
            }
            
            protected override void OnRowChanging(DataRowChangeEventArgs e) {
                base.OnRowChanging(e);
                if ((this.TUsersRowChanging != null)) {
                    this.TUsersRowChanging(this, new TUsersRowChangeEvent(((TUsersRow)(e.Row)), e.Action));
                }
            }
            
            protected override void OnRowDeleted(DataRowChangeEventArgs e) {
                base.OnRowDeleted(e);
                if ((this.TUsersRowDeleted != null)) {
                    this.TUsersRowDeleted(this, new TUsersRowChangeEvent(((TUsersRow)(e.Row)), e.Action));
                }
            }
            
            protected override void OnRowDeleting(DataRowChangeEventArgs e) {
                base.OnRowDeleting(e);
                if ((this.TUsersRowDeleting != null)) {
                    this.TUsersRowDeleting(this, new TUsersRowChangeEvent(((TUsersRow)(e.Row)), e.Action));
                }
            }
            
            public void RemoveTUsersRow(TUsersRow row) {
                this.Rows.Remove(row);
            }
        }
        
        [System.Diagnostics.DebuggerStepThrough()]
        public class TUsersRow : DataRow {
            
            private TUsersDataTable tableTUsers;
            
            internal TUsersRow(DataRowBuilder rb) : 
                    base(rb) {
                this.tableTUsers = ((TUsersDataTable)(this.Table));
            }
            
            public int userId {
                get {
                    return ((int)(this[this.tableTUsers.userIdColumn]));
                }
                set {
                    this[this.tableTUsers.userIdColumn] = value;
                }
            }
            
            public int coId {
                get {
                    return ((int)(this[this.tableTUsers.coIdColumn]));
                }
                set {
                    this[this.tableTUsers.coIdColumn] = value;
                }
            }
            
            public string firstName {
                get {
                    return ((string)(this[this.tableTUsers.firstNameColumn]));
                }
                set {
                    this[this.tableTUsers.firstNameColumn] = value;
                }
            }
            
            public string lastName {
                get {
                    return ((string)(this[this.tableTUsers.lastNameColumn]));
                }
                set {
                    this[this.tableTUsers.lastNameColumn] = value;
                }
            }
            
            public string userName {
                get {
                    return ((string)(this[this.tableTUsers.userNameColumn]));
                }
                set {
                    this[this.tableTUsers.userNameColumn] = value;
                }
            }
            
            public string password {
                get {
                    return ((string)(this[this.tableTUsers.passwordColumn]));
                }
                set {
                    this[this.tableTUsers.passwordColumn] = value;
                }
            }
            
            public bool anyServer {
                get {
                    return ((bool)(this[this.tableTUsers.anyServerColumn]));
                }
                set {
                    this[this.tableTUsers.anyServerColumn] = value;
                }
            }
            
            public bool inactive {
                get {
                    return ((bool)(this[this.tableTUsers.inactiveColumn]));
                }
                set {
                    this[this.tableTUsers.inactiveColumn] = value;
                }
            }
            
            public int userRole {
                get {
                    return ((int)(this[this.tableTUsers.userRoleColumn]));
                }
                set {
                    this[this.tableTUsers.userRoleColumn] = value;
                }
            }
            
            public string userMode {
                get {
                    return ((string)(this[this.tableTUsers.userModeColumn]));
                }
                set {
                    this[this.tableTUsers.userModeColumn] = value;
                }
            }
        }
        
        [System.Diagnostics.DebuggerStepThrough()]
        public class TUsersRowChangeEvent : EventArgs {
            
            private TUsersRow eventRow;
            
            private DataRowAction eventAction;
            
            public TUsersRowChangeEvent(TUsersRow row, DataRowAction action) {
                this.eventRow = row;
                this.eventAction = action;
            }
            
            public TUsersRow Row {
                get {
                    return this.eventRow;
                }
            }
            
            public DataRowAction Action {
                get {
                    return this.eventAction;
                }
            }
        }
    }
}
