
package com.gensym.gsi.messages;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import java.io.IOException;

public class write_user_message_string implements ICPMessage {
    public static short messageCode = 65;
    private ICPStream stream = null;

    String user_message = null;
    Integer urgency = null;
    Integer duration = null;
    boolean do_not_reformat = false;

    public write_user_message_string () {}
    public write_user_message_string (String user_message, Integer urgency, Integer duration, boolean do_not_reformat) {
        this.user_message = user_message;
        this.urgency = urgency;
        this.duration = duration;
        this.do_not_reformat = do_not_reformat;
    }
    @Override
    public void read (ICPInputStream inputStream)
        throws IOException {
        user_message = TEXT_STRING.read(inputStream);
        urgency = UNSIGNED_INTEGER_OR_NIL.read(inputStream);
        duration = UNSIGNED_INTEGER_OR_NIL.read(inputStream);
        do_not_reformat = DO_NOT_REFORMAT_MESSAGE_P.read(inputStream);
        inputStream.readICPMessageGroupEnd();
    }
    @Override
    public void write (ICPOutputStream outputStream)
        throws IOException {
        stream = outputStream;
        outputStream.writeICPByte(messageCode);
        TEXT_STRING.write(user_message,outputStream);
        UNSIGNED_INTEGER_OR_NIL.write(urgency,outputStream);
        UNSIGNED_INTEGER_OR_NIL.write(duration,outputStream);
        DO_NOT_REFORMAT_MESSAGE_P.write(do_not_reformat,outputStream);
        outputStream.endICPMessageGroup();
    }
    @Override
    public void run (GSISocket sck) throws IOException {
    }
}
