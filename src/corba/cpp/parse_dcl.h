/*							  
 * This file contains the classes for use in building a parse tree before creation of
 * G2 data objects. It has declarations only.
 */

//**************************Class: TopClass***************************
class TopClass		//Abstract
	{
	private:

	protected:
		//g2_file_token		*root;		//This will be the base for the GSI object model.
	
	public:
		TopClass();
		virtual ~TopClass();
		virtual SuperClass *buildGSIobject( SuperClass * ) = 0;		//Makes TopClass abstract
		static char *toUpperPlus( char * );


		virtual void setUnaryOperator( int );		//Used in: Literal (subclasses), Scoped_Name

		//*****End: Methods to be overridden in various subclasses.

	};


//**************************Class: Inheritance_Spec***************************
class Inheritance_Spec : public TopClass
	{
	private:
		TopClass	**scoped_name_array;
		int			scoped_name_array_count;

	protected:
				
	public:
		Inheritance_Spec( void * [], int );
		virtual ~Inheritance_Spec();
		virtual SuperClass *run_scoped_name_array_i_buildGSIobject( int i );	//Provide access to private members.
		virtual int get_scoped_name_array_count();				//Provide access to private members.
		virtual SuperClass *buildGSIobject( SuperClass * );		//Override parent class' version.

	};


//**************************Class: Raises_Expr***************************
class Raises_Expr : public TopClass
	{
	private:
		TopClass	**scoped_name_array;
		int			scoped_name_array_count;

	protected:
				
	public:
		Raises_Expr( void * [], int );
		virtual ~Raises_Expr();
		virtual SuperClass *run_scoped_name_array_i_buildGSIobject( int i );	//Provide access to private members.
		virtual int get_scoped_name_array_count();		//Provide access to private members.
		virtual SuperClass *buildGSIobject( SuperClass * );		//Override parent class' version.

	};
		

//**************************Class: Context_Expr***************************
class Context_Expr : public TopClass
	{
	private:
		char		*keyword;
		TopClass	**string_literal_array;
		int			string_literal_count;
		
	protected:
				
	public:
		Context_Expr( char *, void * [], int );
		virtual ~Context_Expr();
		virtual SuperClass *run_string_literal_array_i_buildGSIobject( int );	//Provide access to private members.
		virtual int get_string_literal_count();		//Provide access to private members.	
		virtual SuperClass *buildGSIobject( SuperClass * );		//Override parent class' version.

	};


//**************************Class: Base_Type_Spec***************************
class Base_Type_Spec : public TopClass
	{
	private:
		char	*string;

	protected:
				
	public:
		Base_Type_Spec( char * );
		virtual ~Base_Type_Spec();
		virtual SuperClass *buildGSIobject( SuperClass * );		//Override parent class' version.
		
	};


//**************************Class: Attr_Dcl***************************
class Attr_Dcl : public TopClass
	{
	private:
		int			readonly_flag;
		char		*keyword;
		TopClass	*param_type_spec_ptr;
		TopClass	**attr_dcl_array;
		int			attr_dcl_array_count;

	protected:
				
	public:
		Attr_Dcl( int, char *, void *, void * [], int );
		virtual ~Attr_Dcl();
		virtual SuperClass *buildGSIobject( SuperClass * );		//Override parent class' version.

	};


//**************************Class: Interface_Body***************************
class Interface_Body : public TopClass
	{
	private:
		TopClass	**export_array;
		int			export_array_count;
		int			export_array_size_limit;
		
	protected:
				
	public:
		Interface_Body();
		virtual ~Interface_Body();
		virtual int get_export_array_count();	//Provide access to private members.
		virtual SuperClass *run_export_array_i_buildGSIobject( int i );	//Provide access to private members.
		virtual void delete_export_array_element( int i );		//Provide access to private members.
		virtual SuperClass *buildGSIobject( SuperClass * );		//Override parent class' version.
		virtual void addExport( void *ptr_arg );
	};

//**************************Class: Interface_Header***************************
class Interface_Header : public TopClass
	{
	private:
		char		*keyword;
		char		*identifier_name;
		TopClass	*inheritance_spec;		
		
	protected:
				
	public:
		Interface_Header( char *, char * );
		Interface_Header( char *, char *, void * );
		virtual ~Interface_Header();
		virtual char *get_identifier_name();					//Provide access to private members.
		virtual TopClass *get_inheritance_spec_ptr();			//Provide access to private members.
		virtual SuperClass *run_inheritance_spec_ptr_buildGSIobject();	//Provide access to private members.
		virtual SuperClass *buildGSIobject( SuperClass * );		//Override parent class' version.
		
	};


//**************************Class: Interface_Dcl***************************
class Interface_Dcl : public TopClass
	{
	private:
		TopClass	*interface_header;
		TopClass	*interface_body;	
		
	protected:
				
	public:
		Interface_Dcl( void *, void * );
		virtual ~Interface_Dcl();
		virtual SuperClass *buildGSIobject( SuperClass * );		//Override parent class' version.
		
	};


//**************************Class: Specification***************************
class Specification : public TopClass
	{
	private:
		TopClass	**definition_array;
		int			definition_array_count;
		int			definition_array_size_limit;
		
	protected:
				
	public:
		Specification();
		virtual ~Specification();				   
		virtual void addDefinition( void *ptr_arg );
		virtual SuperClass *buildGSIobject( SuperClass * );		//Override parent class' version.

	};

//**************************Class: Op_Type_Spec***************************
class Op_Type_Spec : public TopClass
	{
	private:
		char		*string;
		TopClass	*param_type_spec_ptr;

	protected:
				
	public:
		Op_Type_Spec( char * );
		Op_Type_Spec( void * );
		virtual ~Op_Type_Spec();
		virtual SuperClass *run_param_type_spec_ptr_buildGSIobject();	//Provide access to private members.
		virtual char *get_string();		//Provide access to private members.
		virtual TopClass *get_param_type_spec_ptr();			//Provide access to private members.
		virtual SuperClass *buildGSIobject( SuperClass * );		//Override parent class' version.
		
	};
		

//**************************Class: Param_Dcl***************************
class Param_Dcl : public TopClass
	{
	private:
		char		*param_attribute;
		TopClass	*param_type_spec_ptr;
		TopClass	*simple_declarator;
		
	protected:
				
	public:
		Param_Dcl( char *, void *, void * );
		virtual ~Param_Dcl();
		virtual SuperClass *buildGSIobject( SuperClass * );		//Override parent class' version.

	};


//**************************Class: Op_Dcl***************************
//NOTE: Handling of context_expr is not yet implemented!
class Op_Dcl : public TopClass
	{
	private:
		int			opattribute_flag;
		TopClass	*op_type_spec_ptr;
		char		*operation_name;
		TopClass	**param_dcl_array;
		int			param_dcl_array_count;
		TopClass	*raises_expr_ptr;
		TopClass	*context_expr_ptr;

	protected:
				
	public:
		Op_Dcl( int, void *, char *, void * [], int, void *, void * );
		virtual ~Op_Dcl();
		virtual SuperClass *buildGSIobject( SuperClass * );		//Override parent class' version.

	};


//**************************Class: Enum_Type***************************
class Enum_Type : public TopClass
	{
	private:
		char		*keyword;
		char		*enum_name;
		char		**enumerator_array;
		int			enumerator_array_count;
		
	protected:
				
	public:
		Enum_Type( char *, char *, char * [], int );
		virtual ~Enum_Type();
		virtual SuperClass *buildGSIobject( SuperClass * );		//Override parent class' version.

	};

//**************************Class: Simple_Declarator***************************
class Simple_Declarator : public TopClass
	{
	private:
		char	*string;

	protected:
				
	public:
		Simple_Declarator( char * );
		virtual ~Simple_Declarator();
		virtual SuperClass *buildGSIobject( SuperClass * );		//Override parent class' version.
		
	};
		

//**************************Class: Member***************************
//***NOTE: Virtually identical to Type_Declarator class***
class Member : public TopClass
	{
	private:
		TopClass	*type_spec_ptr;
		TopClass	**declarator_array;
		int			declarator_array_count;

	protected:
				
	public:
		Member( void *, void * [], int );
		virtual ~Member();
		virtual SuperClass *run_type_spec_ptr_buildGSIobject();	//Provide access to private members.
		virtual SuperClass *run_declarator_array_buildGSIobject( int );	//Provide access to private members.
		virtual int get_declarator_array_count();				//Provide access to private members.		
		virtual SuperClass *buildGSIobject( SuperClass * );		//Override parent class' version.

	};


//**************************Class: Struct_Type***************************
class Struct_Type : public TopClass
	{
private:
		char		*keyword;
		char		*struct_name;
		TopClass	**member_array;
		int			member_array_count;

	protected:
				
	public:
		//Struct_Type( void * );
		Struct_Type( char *, char *, void * [], int );
		virtual ~Struct_Type();
		virtual SuperClass *buildGSIobject( SuperClass * );		//Override parent class' version.

	};


//**************************Class: Scoped_Name***************************
class Scoped_Name : public TopClass
	{
	private:
		char		**scoped_name_list_array;
		int			scoped_name_list_array_count;
		int			unary_operator;
		int			scoped_name_scope_flag;

	protected:
				
	public:
		Scoped_Name( char * [], int, int );
		virtual ~Scoped_Name();
		virtual	void setUnaryOperator( int );
		virtual SuperClass *buildGSIobject( SuperClass * );		//Override parent class' version.

	};

		 
//**************************Class: Literal*************************** Each specific literal type has its own subclass.
class Literal : public TopClass
	{
	private:
		
	protected:
				
	public:
		Literal();
		virtual ~Literal();
		virtual int applyUnaryOperator() = 0;					//Make this an abstract class.

		//virtual void setUnaryOperator( int ) = 0;
		virtual SuperClass *buildGSIobject( SuperClass * );		//Override parent class' version.
		
	};


//**************************Class: LongIntegerLiteral***************************
class LongIntegerLiteral : public Literal
	{
	private:
		long		value_member;
		int			unary_operator;

	protected:
				
	public:
		LongIntegerLiteral( long );
		virtual ~LongIntegerLiteral();
		virtual int applyUnaryOperator();
		virtual void setUnaryOperator( int );
		virtual long getValue();
		virtual void setValue( long longInt_arg );
		virtual SuperClass *buildGSIobject( SuperClass * );		//Override TopClass' version.
		
	};


//**************************Class: StringLiteral***************************
class StringLiteral : public Literal
	{
	private:
		char		*value_member;

	protected:
				
	public:
		StringLiteral( char * );
		virtual ~StringLiteral();
		virtual int applyUnaryOperator();
		virtual void setUnaryOperator( int );
 
		//virtual long getValue();
		//virtual void setValue( long longInt_arg );
		virtual SuperClass *buildGSIobject( SuperClass * );		//Override TopClass' version.
		
	};


//**************************Class: CharLiteral***************************
class CharLiteral : public Literal
	{
	private:
		char		value_member;

	protected:
				
	public:
		CharLiteral( char );
		virtual ~CharLiteral();
		virtual int applyUnaryOperator();
		virtual void setUnaryOperator( int );

		//virtual long getValue();
		//virtual void setValue( long longInt_arg );
		virtual SuperClass *buildGSIobject( SuperClass * );		//Override TopClass' version.
		
	};


//**************************Class: DoubleLiteral***************************
class DoubleLiteral : public Literal
	{
	private:
		double		value_member;
		int			unary_operator;

	protected:
				
	public:
		DoubleLiteral( double );
		virtual ~DoubleLiteral();
		virtual int applyUnaryOperator();
		virtual void setUnaryOperator( int );

		virtual double getValue();
		virtual void setValue( double dbl_arg );
		virtual SuperClass *buildGSIobject( SuperClass * );		//Override TopClass' version.
		
	};


//**************************Class: BooleanLiteral***************************
class BooleanLiteral : public Literal
	{
	private:
		char		*value_member;

	protected:
				
	public:
		BooleanLiteral( char * );
		virtual ~BooleanLiteral();
		virtual int applyUnaryOperator();
		virtual void setUnaryOperator( int );
		//virtual long getValue();
		//virtual void setValue( long longInt_arg );
		virtual SuperClass *buildGSIobject( SuperClass * );		//Override TopClass' version.
		
	};


//**************************Class: Except_Dcl***************************
class Except_Dcl : public TopClass
	{
private:
		char		*keyword;
		char		*except_name;
		TopClass	**member_array;
		int			member_array_count;

	protected:
				
	public:
		Except_Dcl( char *, char *, void * [], int );
		virtual ~Except_Dcl();
		virtual SuperClass *buildGSIobject( SuperClass * );		//Override parent class' version.

	};


//**************************Class: Const_Type***************************
class Const_Type : public TopClass
	{
	private:
		char		*string;
		TopClass	*ptr;

	protected:
				
	public:
		Const_Type( char * );
		Const_Type( void * );
		virtual ~Const_Type();		
		virtual TopClass *get_ptr();							//Provide access to private members.
		virtual char *get_string();								//Provide access to private members.
		virtual SuperClass *run_ptr_buildGSIobject();			//Provide access to private members.
		virtual SuperClass *buildGSIobject( SuperClass * );		//Override parent class' version.
		
	};
		

//**************************Class: Const_Dcl*******************
class Const_Dcl : public TopClass
	{
	private:
		char		*keyword;
		TopClass	*const_type_ptr;
		char		*name;
		TopClass	*const_exp_ptr;
		
	protected:
				
	public:
		Const_Dcl( char *, void *, char *, void * );
		virtual ~Const_Dcl();
		virtual SuperClass *buildGSIobject( SuperClass * );		//Override parent class' version.

	};
		

//**************************Class: String_Type***************************
class String_Type : public TopClass
	{
	private:
		char		*keyword;
		TopClass	*positive_int_const_ptr;

	protected:
				
	public:
		String_Type( char *, void * );
		virtual ~String_Type();
		virtual SuperClass *buildGSIobject( SuperClass * );		//Override parent class' version.
		
	};


//**************************Class: Switch_Type_Spec***************************
class Switch_Type_Spec : public TopClass
	{
	private:
		char		*string;
		TopClass	*ptr;

	protected:
				
	public:
		Switch_Type_Spec( char * );
		Switch_Type_Spec( void * );
		virtual ~Switch_Type_Spec();
		virtual SuperClass *buildGSIobject( SuperClass * );		//Override parent class' version.
		
	};
		

//**************************Class: Element_Spec***************************
class Element_Spec : public TopClass
	{
	private:								
		TopClass	*type_spec_ptr;
		TopClass	*declarator_ptr;
		
	protected:
				
	public:
		Element_Spec( void *, void * );
		virtual ~Element_Spec();
		virtual SuperClass *run_declarator_ptr_buildGSIobject();	//Provide access to private members.
		virtual SuperClass *run_type_spec_ptr_buildGSIobject();		//Provide access to private members.
		virtual SuperClass *buildGSIobject( SuperClass * );			//Override parent class' version.

	};


//**************************Class: Case_Label***************************
class Case_Label : public TopClass
	{
	private:
		char		*string;
		TopClass	*const_exp_ptr;

	protected:
				
	public:
		Case_Label( char *, void * );
		virtual ~Case_Label();
		virtual SuperClass *buildGSIobject( SuperClass * );		//Override parent class' version.
  
	};


//**************************Class: Case***************************
class Case : public TopClass
	{
	private:
		TopClass	**case_label_array;
		int			case_label_array_count;
		TopClass	*element_spec_ptr;

	protected:
				
	public:
		Case( void * [], int, void * );
		virtual ~Case();
		virtual SuperClass *run_element_spec_ptr_buildGSIobject();	//Provide access to private members.
		virtual int get_case_label_array_count();					//Provide access to private members.
		virtual SuperClass *run_case_label_array_buildGSIobject( int );	//Provide access to private members.
		virtual SuperClass *buildGSIobject( SuperClass * );			//Override parent class' version.

	};
 

//**************************Class: Union_Type***************************
class Union_Type : public TopClass
	{
	private:
		char		*keyword;
		char		*union_name;
		char		*string;
		TopClass	*switch_type_spec_ptr;
		TopClass	**switch_body_array;
		int			switch_body_array_count;
		
	protected:
				
	public:
		Union_Type( char *, char *, char *, void *, void * [], int );
		virtual ~Union_Type();
		virtual SuperClass *buildGSIobject( SuperClass * );		//Override parent class' version.

	};
 

//**************************Class: Sequence_Type*******************
class Sequence_Type : public TopClass
	{
	private:
		char		*keyword;
		TopClass	*simple_type_spec_ptr;
		TopClass	*positive_int_const_ptr;
		
	protected:
				
	public:
		Sequence_Type( char *, void *, void * );
		virtual ~Sequence_Type();
		virtual SuperClass *buildGSIobject( SuperClass * );		//Override parent class' version.

	};
		

//**************************Class: Array_Declarator***************************
class Array_Declarator : public TopClass
	{
	private:
		char		*array_name;
		TopClass	**fixed_array_size_array;
		int			fixed_array_size_count;		

	protected:
				
	public:
		Array_Declarator( char *, void * [], int );
		virtual ~Array_Declarator();
		virtual SuperClass *buildGSIobject( SuperClass * );		//Override parent class' version.

	};
		

//**************************Class: Type_Declarator***************************
//***NOTE: Virtually identical to Member class***
class Type_Declarator : public TopClass
	{
	private:
		TopClass	*type_spec_ptr;
		TopClass	**declarator_array;
		int			declarator_array_count;

	protected:
				
	public:
		Type_Declarator( void *, void * [], int );
		virtual ~Type_Declarator();
		virtual SuperClass *run_type_spec_ptr_buildGSIobject();	//Provide access to private members.
		virtual SuperClass *run_declarator_array_buildGSIobject( int );	//Provide access to private members.
		virtual int get_declarator_array_count();				//Provide access to private members.		
		virtual SuperClass *buildGSIobject( SuperClass * );		//Override parent class' version.

	};
		
 
//**************************Class: Type_Dcl_Case1***************************
class Type_Dcl_Case1 : public TopClass
	{
	private:
		char		*keyword;
		TopClass	*type_declarator_ptr;

	protected:
				
	public:
		Type_Dcl_Case1( char *, void * );
		virtual ~Type_Dcl_Case1();
		virtual SuperClass *buildGSIobject( SuperClass * );		//Override parent class' version.
  
	};


//**************************Class: Forward_Dcl***************************
class Forward_Dcl : public TopClass
	{
	private:
		char		*keyword;
		char		*identifier_name;		
		
	protected:
				
	public:
		Forward_Dcl( char *, char * );
		virtual ~Forward_Dcl();
		virtual SuperClass *buildGSIobject( SuperClass * );		//Override parent class' version.		
	};


//**************************Class: Module***************************
class Module : public TopClass
	{
	private:
		char		*keyword;
		char		*module_name;
		TopClass	**module_definition_array;
		int			module_definition_count;
	
	protected:
				
	public:
		Module( char *, char *, void * [], int );
		virtual ~Module();
		virtual SuperClass *buildGSIobject( SuperClass * );		//Override parent class' version.

	};
		

//**************************Class: Math_Expression***************************
//This class will handle the mult_expr, add_expr, shift_expr, and_expr, xor_expr, 
//and or_expr cases in the parser file. Each object will have a math op passed in 
//when it is constructed.
class Math_Expression : public TopClass
	{
	private:								
		TopClass	*left_operand_ptr;		//Each operand could be a literal or another 
		TopClass	*right_operand_ptr;		//Math_Expression object.
		int			operator_code;
		
	protected:
				
	public:
		Math_Expression( void *, void *, int );
		virtual ~Math_Expression();
		virtual SuperClass *buildGSIobject( SuperClass * );		//Override parent class' version.

	};
