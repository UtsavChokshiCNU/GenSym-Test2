Apologies first:

I have not taken the time to figure out how to achieve our javadoc
build needs by subclassing the Standard doclet. It actually shouldn't be
that hard, I just haven't taken the time.

Purpose:
To generate javadoc for our products that satisfies the following
specialized needs not currently satisfied by the standard javadoc
tool:
1. To exclude methods and fields that have the @undocumented tag
2. To exclude classes that are listed as exclude-from-javadoc in
   the package.info for their package
3. In the future, this tool should be modified (if necessary)

NOTE:
This tool is presumed to be used with a list of packages. The making
of this list of packages is what takes into account the other relevant
package.info entries, "package-is-private: true" and "dont-jar-package: true"
and "dont-delete-java: true".



In package com.gensym.devtools.doclets:

1. Added -noundocumented switch to Configuration.java

2. modified buildTree in ClassTree.java to call excludeClass

3. modified shouldAddToIndexMap in IndexBuilder to check "undocumented"

In package com.gensym.devtools.doclets.standard:

1. modified eligibleMembers in AbstractSubWriter to check "undocumented".
   Also changed nodeprecated usage.

2. Added -noundocumented  and -root switch to ConfigurationStandard.java
   NOTE: the -noundocumented switch is really ignored (it is actually
   assumed to be true, i.e., this doclet will never print @undocumented
   elements).

3. No change needed to HelpWriter or HtmlStandardWriter, because
   the noDeprecated applies to links

4. No change needed to PackageTreeWriter because noDeprecated applies
   to argument passed to ClassTree

5. modified generateClassKindListing in PackageWriter to call excludeClass

6. modified generateClassCycle in Standard to call excludeClass
