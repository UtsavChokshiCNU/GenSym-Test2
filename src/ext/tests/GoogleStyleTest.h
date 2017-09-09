#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>


// GoogleStyleTest is used for simplify define a test
// User could refer to CStreamsTests.cpp as an example

template <typename T>
class GoogleStyleTest: public CPPUNIT_NS::TestFixture {
  public:                                                                   
    typedef T TestFixtureType;                               
    
	typedef void (TestFixtureType::*MethodType)();
	typedef std::pair< std::string, MethodType> TestType;
	typedef std::vector< TestType > TestsType;

	//This class is used for auto register the test
	template <typename U>
	class TestRegister{
	public:
	  TestRegister(const std::string &methodName, MethodType fnPtr){
		        TestType test = std::make_pair(methodName, fnPtr);
			GoogleStyleTest<U>::getTests().push_back(test);
		}
	};

	typedef TestRegister<T> RegisterType;


  private:                                                                  
    static const CPPUNIT_NS::TestNamer &getTestNamer__()                    
    {                                                                       
      static CPPUNIT_TESTNAMER_DECL( testNamer, T );         
      return testNamer;                                                     
    }

  protected:


	//Get all the tests for this suite
	static TestsType& getTests(){
		static TestsType tests;
		return tests;
	}
                                                                            
  public:                                                                   
    typedef CPPUNIT_NS::TestSuiteBuilderContext<TestFixtureType>            
                TestSuiteBuilderContextType;                                
       


    static void                                                             
    addTestsToSuite( CPPUNIT_NS::TestSuiteBuilderContextBase &baseContext ) 
    {                                                                       
      TestSuiteBuilderContextType context( baseContext );

	  //The same fixture should only be registered for one time
	  static bool alreadyAdded;
	  if(alreadyAdded){
		return;
	  }
	  alreadyAdded = true;
	  TestsType const& tests = getTests();
	  
	  for(typename TestsType::const_iterator it = tests.begin(); it != tests.end(); ++it){
		  const TestType& test = *it;

		  CPPUNIT_TEST_SUITE_ADD_TEST(
			  new CPPUNIT_NS::TestCaller<TestFixtureType>(    
				context.getTestNameFor( test.first ),   
				test.second,           
				context.makeFixture()));
	  }

	  //tests.clear();

	  CPPUNIT_TEST_SUITE_END();
};

                           
#define TEST_F(methodName, FixtureName) \
	static GoogleStyleTest<FixtureName>::RegisterType \
	s##methodName##FixtureName(#methodName, &FixtureName::methodName);\
	CPPUNIT_TEST_SUITE_REGISTRATION(FixtureName);\
	void FixtureName::methodName()

#define TEST(methodName) \
	class methodName##GoogleStyleTest: public GoogleStyleTest<methodName##GoogleStyleTest> { \
	public: \
		void methodName(); \
	}; \
	TEST_F(methodName, methodName##GoogleStyleTest)
