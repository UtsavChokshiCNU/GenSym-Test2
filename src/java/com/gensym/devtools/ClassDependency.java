
package com.gensym.devtools;

class ClassDependency {

  String dependentClassName;
  String[] dependencies;

  ClassDependency (String dependentClassName,
		   String[] dependencies) {
    this.dependentClassName = dependentClassName;
    this.dependencies = dependencies;
  }

}
