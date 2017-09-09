package com.gensym.dispatcher;

public class SwitchDecision extends Decision {
  Reference referenceSwitch;
  Decision currentDecision = null;
  boolean setDefault = false, setRoot = false;
  
  private Condition newCase(int constCase) {
    return new SimpleCondition(SimpleCondition.EQUAL,
			       referenceSwitch,
			       new ConstantReference(Integer.TYPE,
						     new Integer(constCase)));
  }

  private Condition newCase(Object constCase) {
    return new SimpleCondition(SimpleCondition.EQUAL,
			       referenceSwitch,
			       new ConstantReference(constCase));
  }

  public SwitchDecision(Reference reference) {
    super(new FalseCondition(),new Noop(),new Noop());
    currentDecision = this;
    referenceSwitch = reference;
  }

  public void addCase(Object constCase, Node node){
    if (setDefault) return;
    if (setRoot) {
      Decision nextDecision = new Decision(newCase(constCase),node,new Noop());
      currentDecision.setFalseNode(nextDecision);
      currentDecision = nextDecision;
    } else {
      setCondition(newCase(constCase));
      setTrueNode(node);
      setRoot = true;
    }
    //System.out.println("add case " + constCase + node + " to\n" + this);
  }

  public void addCase(int constCase, Node node){
    if (setDefault) return;
    if (setRoot) {
      Decision nextDecision = new Decision(newCase(constCase),node,new Noop());
      currentDecision.setFalseNode(nextDecision);
      currentDecision = nextDecision;
    } else {
      setCondition(newCase(constCase));
      setTrueNode(node);
      setRoot = true;
    }
    //System.out.println("add case " + constCase + node + " to\n" + this);
  }

  public void setDefault(Node node)
  {
    
    currentDecision.setFalseNode(node);
    setDefault = true;
  }

  @Override
  public String toString() {
    String str = "switch (" + referenceSwitch + ") {\n";
    Node nextD = this;
    while (nextD instanceof Decision) {
      Condition cond = ((Decision)nextD).getCondition();
      if (cond instanceof SimpleCondition) {
	Reference nextConstCase = ((SimpleCondition)cond).getRef2();
	Node nextCaseDo = ((Decision)nextD).getTrueNode();
	nextD = ((Decision)nextD).getFalseNode();
	str+= "case " + nextConstCase + ": \n" + nextCaseDo + " \nbreak;\n";
      } else
	return super.toString();
    }
    if (setDefault)
      str+= "default: " + nextD + "\n";
    str+="}";
    return str;
  }    
}
  
