package gensym;

// SCS, or simple client state, provides a way to maintain data
// in a java application that maybe updated by G2.  The updates
// are in the form of HTTP resouces of type text/simple - which
// makes them readable when your developing and testing the bridge.
// The data is maintained a pool three element tuples and operations
// to lookup elements, iterate, and delete are provided.

// The data consists of a set of triples (assertions if you will).
// A readable dump of a tiny SCS instance might look like this:
//      global user-name "bob"
//      global email-address "bob@foo.com"
//      handles pump 1243
//      1243 temp 23.4
//      1243 rate 34.3

// The G2 generated text that would create those entries might 
// look like this:
//      global user-name "bob" @assert
//      global email-address "bob@foo.com" @assert
//      handles pump 1243 @assert
//      1243 temp 23.4 @assert
//      1243 rate 34.3 @assert

// This mechinism is implemented very simply, it is not intended
// for huge pools of data, For a hundred or fewer tuples it should
// be sufficent.

package gensym

class SCS {
  // The Java programmer may query this data using the following
  // routines:

  // Check if a tuple appears in the database.
  public Boolean tupleExists(Object A, Object B, Object C){
  }
  
  // Used in queries to as a wildcard.
  public constant Object wildcardTuple;

  // Used to fetch a value, one of the elements must be a wildcard.
  public Object tupleLookup(Object A, Object B, Object C){
  }

  // We can iterate over a set of tuples, one or more of these
  // objects maybe a wildcard.
  public TupleGenerator startTupleGenerator(Object A, Object B, Object C){
  }

  // Give a generator this will return the first, second or
  // third of the data tuple's elements
  public Object nextTupleValueA(TupleGenerator tupleGenerator){
  }

  public Object nextTupleValueB(TupleGenerator tupleGenerator){
  }

  public Object nextTupleValueC(TupleGenerator tupleGenerator){
  }

  // Check if the generator is done.
  public boolean eofGenerator(TupleGenerator g){
  }

  // Moves to the next available value, indicate if we are node.
  public boolean advanceGeneator(TupleGenerator g){
  }

  // Remove all tuples matching the pattern given
  public void deleteTuples(Object A, Object B, Object C){
  }


 }
