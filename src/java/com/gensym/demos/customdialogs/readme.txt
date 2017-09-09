

By default, every G2 item is edited using a dialog generated from
introspection of the class.

This demo shows how to override this default behaviour and allow
use of custom dialogs to edit items. The overrides are of two
type:

(1) Overriding at the class level : i.e. to use a single custom
      dialog to edit every instance of a class.
(2) Overriding at the instance level : i.e. to specify a custom
      dialog for specific G2 items.

In order to override the default behavior, the DialogManager on the
client must be informed of the resources to use. This can be done by
calling the rpc set-dialog-resource-entry, which is provided in
sequoia-support.kb. In the demo, demo-dialog-registration-procedure
calls this rpc 3 times : once to specify overrides for the class
DIAL, once for the item named JUGHEAD, and finally for the item
named JOHNNY. The first two resources are located in the KB in
a media-bin whereas the third is located on disk. You may also
specify any arbitrary URL (with a known protocol such as
http, ftp, gopher etc.) as the location of the resource.

Run the demo as follows:

On Windows NT: run 

% rundemo.bat

On Solaris: run

% rundemo.sh

This starts up G2 with the dialog-demo KB. It also starts up the
prototype shell to connect to the KB. Use File -> Get Workspace
to display the CUSTOM-DIALOG-DEMO workspace. Use the right mouse
button to display the property editor for each item on the workspace.
Note that generated dialogs are used whenever overrides are not
specified.

KNOWN BUG:
==========

On Windows NT, after entering a new value in the text field, you
must hit return to retain the new value. Do not TAB out of the
field without hitting return.