#define CATCH_CONFIG_MAIN   //use main of catch framework
#define CATCH_CONFIG_NO_CPP11 //use catch without cpp 11

#include <fstream>
#include <string>
#include"catch.hpp"

#ifdef _WIN32
#include <Windows.h>
#define msleep Sleep
#define SLEEP_FACTOR 1000
#else
#define msleep sleep
#define SLEEP_FACTOR 1
#endif

#define MQTT_SEVEN_DAYS 604800

extern "C"{
#include"mqttclient.h"
#include"mqttSessionTrace.h"
#include"mqttDataTrace.h"
}

int ValidateFile(char const* path, char const* commands[], int count)
{
    std::string str; 
    int i=0;
    std::ifstream file(path, std::ifstream::in);

    REQUIRE(file.is_open());
    
    while (std::getline(file, str))
    {
        REQUIRE( i < count );
        if (!str.empty() && i<count) {
            REQUIRE(str.find(commands[i])!=-1);
            i++;
        } 
    }

    file.close();
    return mqtt_success;
}

TEST_CASE("Testing creation of MQTT Context")
{
    struct MQTTContext ctx;
    struct MQTTBroker brkr;
    struct MQTTConnection conn;
    int result = CreateMQTTContext(&ctx, &brkr, &conn);
    REQUIRE(result == 0);
    REQUIRE(ctx.MQTTHandle != 0);
}

TEST_CASE("Test Session Trace")
{
    char server[] = "127.0.0.1";
    char path[] = "";
    char PacketID[] = "SamplePacketID:1230912831239081232244redw2222222";

    remove("127_0_0_1_ControlPacket_01.log");

    mqtt_pts_t pts = mqtt_make_packet_trace_params(server, path,MQTT_SEVEN_DAYS);

    REQUIRE(pts.mqtt_logging_last_error == mqtt_success);
    REQUIRE(pts.filePath != NULL);

    REQUIRE(mqtt_success ==  mqtt_trace_packet_CONNACK(&pts, 0, 23222));

    REQUIRE(mqtt_success ==  mqtt_trace_packet_CONNECT(&pts, "123123123123",  '1',  1,  0,  1,  2,  1,  0,  60,  "amhmekdkwe fsdfsdfsdfssfsd/sdfjiiritjlfkdjgdfklgjdf",  "Hello World",  "ahmedkorany@devfatory.com",  ""));

    REQUIRE(mqtt_success == mqtt_trace_packet_PUBLISH(&pts, 1, 1, "/Test_Topic_Path/Topic_Name", 123, "Hello MQTT Message 001"));

    REQUIRE(mqtt_success ==  mqtt_trace_packet_PUBACK(&pts, PacketID));

    REQUIRE(mqtt_success ==  mqtt_trace_packet_PUBREC(&pts, PacketID));

    REQUIRE(mqtt_success == mqtt_trace_packet_PUBREL(&pts, PacketID));

    REQUIRE(mqtt_success == mqtt_trace_packet_PUBCOMP(&pts, PacketID));

    mqtt_sub_topic topics[3];

    topics[0].topicname = (char *) malloc(strlen("/Test_Topic_Path/Multi_Topic_1")+1);
    strcpy(topics[0].topicname, "/Test_Topic_Path/Multi_Topic_1");
    topics[0].QoS = 1;
    topics[1].topicname = (char *) malloc(strlen("/Test_Topic_Path/Multi_Topic_2")+1);
    strcpy(topics[1].topicname, "/Test_Topic_Path/Multi_Topic_2");
    topics[1].QoS = 2;
    topics[2].topicname = (char *) malloc(strlen("/Test_Topic_Path/Multi_Topic_3")+1);
    strcpy(topics[2].topicname, "/Test_Topic_Path/Multi_Topic_3");
    topics[2].QoS = 2;

    REQUIRE(mqtt_success ==  mqtt_trace_packet_SUBSCRIBE(&pts, PacketID, topics,  3));

    short retCodes[] = {1, 2, 2};
    REQUIRE(mqtt_success ==  mqtt_trace_packet_SUBACK(&pts, PacketID, retCodes, 3));

    REQUIRE(mqtt_success == mqtt_trace_packet_UNSUBSCRIBE(&pts, PacketID, topics, 3));

    REQUIRE(mqtt_success == mqtt_trace_packet_UNSUBACK(&pts, PacketID));

    REQUIRE(mqtt_success == mqtt_trace_packet_PINGREQ(&pts));

    REQUIRE(mqtt_success == mqtt_trace_packet_PINGRESP(&pts));

    REQUIRE(mqtt_success == mqtt_trace_packet_DISCONNECT(&pts));

    SECTION("Check the file exists with the proper name and size")
    {
        //Commands order is important , make it identical to API calls happened above.
        char const* commands[] = {"CONNACK", "CONNECT" , "PUBLISH" , "PUBACK" , "PUBREC" , "PUBREL" , "PUBCOMP" ,"SUBSCRIBE", "Multi_Topic_1" , "Multi_Topic_2" , 
            "Multi_Topic_3","SUBACK","UNSUBSCRIBE","Multi_Topic_1","Multi_Topic_2","Multi_Topic_3","UNSUBACK","PINGREQ","PINGRESP","DISCONNECT"};
        REQUIRE(mqtt_success == ValidateFile("127_0_0_1_ControlPacket_01.log",commands,20));  
    }
}

TEST_CASE("TEST Session Trace Switch ON/OFF")
{
    char server[] = "SESSION-ONOFF";
    char PacketID[] = "TESTSWITCHONPACKET:12309128312390812322442222222";
    remove("SESSION-ONOFF_ControlPacket_01.log");
    mqtt_pts_t pts = mqtt_make_packet_trace_params(server, NULL, MQTT_SEVEN_DAYS);
    
    REQUIRE(pts.mqtt_logging_last_error == mqtt_success);

    mqtt_trace_session_turnOff(&pts);
    
    REQUIRE(pts.isON == 0 );

    REQUIRE(mqtt_error_trace_turned_off == mqtt_trace_packet_PUBLISH(&pts, 1, 1, "/Test_Topic_Path/Topic_Name", 123, "Hello MQTT Message 001"));

    REQUIRE(mqtt_error_trace_turned_off == mqtt_trace_packet_PUBACK(&pts, PacketID));

    REQUIRE(mqtt_error_trace_turned_off ==  mqtt_trace_packet_PUBREC(&pts, PacketID));

    REQUIRE(mqtt_error_trace_turned_off == mqtt_trace_packet_PUBREL(&pts, PacketID));

    REQUIRE(mqtt_error_trace_turned_off == mqtt_trace_packet_PUBCOMP(&pts, PacketID));

    SECTION("Check the file doesn't exists")
    {
       std::ifstream p_file("SESSION-ONOFF_ControlPacket_01.log", std::fstream::in | std::fstream::binary);
       REQUIRE(!p_file.is_open());
    }
    
    mqtt_trace_session_turnOn(&pts);

    REQUIRE(mqtt_success == mqtt_trace_packet_PUBLISH(&pts, 1, 1, "/Test_Topic_Path/Topic_Name", 123, "Hello MQTT Message 001"));

    REQUIRE(mqtt_success == mqtt_trace_packet_PUBACK(&pts, PacketID));

    REQUIRE(mqtt_success == mqtt_trace_packet_PUBREC(&pts, PacketID));

    REQUIRE(mqtt_success ==mqtt_trace_packet_PUBREL(&pts, PacketID));

    REQUIRE(mqtt_success == mqtt_trace_packet_PUBCOMP(&pts, PacketID));

    SECTION("Check the file exists with the proper name and valid contents")
    {
        //Commands order is important , make it identical to API calls happened above.
        char const* commands[] = {"PUBLISH", "PUBACK" , "PUBREC" , "PUBREL", "PUBCOMP"};
        REQUIRE(mqtt_success == ValidateFile("SESSION-ONOFF_ControlPacket_01.log", commands, 5));
    }
}

TEST_CASE("Testing Session Trace with none default file path")
{
    char *cwd = NULL;
    cwd = getcwd(cwd,  PATH_LENGTH + 1);

    if (cwd == 0) {
        std::cout << "Warnning ! : couldn't retrive current working directory , this is not failure on the client under test but in test module will skip this test case";
        return;
    }
    int idx = (int)(strrchr(cwd, PATH_SEP)- cwd + 1);
    std::string path(cwd, 0, idx);

    char server[] = "10.1.1.1";
    char PacketID[] = "SamplePacketID:None Default path";
    
    std::string full_path(path);
    full_path=full_path.append("10_1_1_1_ControlPacket_01.log");
    remove(full_path.c_str());

    mqtt_pts_t pts = mqtt_make_packet_trace_params(server, path.c_str(), MQTT_SEVEN_DAYS);
    REQUIRE(pts.mqtt_logging_last_error == mqtt_success);

    REQUIRE(mqtt_success ==  mqtt_trace_packet_CONNECT(&pts, "123123123123",  '1',  1,  0,  1,  2,  1,  0,  60,  "amhmekdkwe",  "Hello World",  "ahmedkorany@devfatory.com",  ""));

    SECTION("Check the file exists with the proper name and valid contents")
    {
        //Commands order is important , make it identical to API calls happened above.
        char const* commands[] = {"CONNECT"};
        REQUIRE(mqtt_success == ValidateFile(pts.filePath, commands, 1));
    }

}

TEST_CASE("Test Data Trace")
{
    char server[] = "127.0.0.1";
    char ipath[] = "";
    remove("127_0_0_1_MessageData_01.log");
    mqtt_dtp_t dtp = mqtt_make_topic_data_trace(server, ipath, MQTT_SEVEN_DAYS);
    REQUIRE(dtp.mqtt_logging_last_error == mqtt_success);
    REQUIRE(mqtt_success == mqtt_tdt_published(&dtp, "/Test_Data_Trace_Root/Topic_Name_Data_Trace", 1, "jlkerlkjqew.213213edasaaaa"));

    REQUIRE(mqtt_success == mqtt_tdt_received(&dtp, "/Test_Data_Trace_Root/Topic_Name_Data_Received", 2, "kf;sdlkfw3wdnnddww/s33 wdsllwe3322 !@$^&&*(*&"));

    SECTION("Check the file exists with the proper name and size and valid contents")
    {
        //Commands order is important , make it identical to API calls happened above.
        char const* commands[] = {"Published_data", "Received_data"};
        REQUIRE(mqtt_success == ValidateFile("127_0_0_1_MessageData_01.log", commands, 2));
    }

}

TEST_CASE("Test Data Trace Error Cases")
{
    char path[] = "";

    mqtt_dtp_t dtp = mqtt_make_topic_data_trace(NULL, path, MQTT_SEVEN_DAYS);
    REQUIRE(dtp.mqtt_logging_last_error != mqtt_success);

    REQUIRE(mqtt_success != mqtt_tdt_published(&dtp, "/Test_Data_Trace_Root/Topic_Name_Data_Trace", 1, "jlkerlkjqew.213213edasaaaa"));

    REQUIRE(mqtt_success != mqtt_tdt_received(&dtp, "/Test_Data_Trace_Root/Topic_Name_Data_Received", 2, "kf;sdlkfw3wdnnddww/s33 wdsllwe3322 !@$^&&*(*&"));

}

TEST_CASE("TEST Data Trace Switch ON/OFF")
{
    char server[] = "DATA-ONOFF";
    int ret = 0;
    
    remove("DATA-ONOFF_MessageData_01.log");

    mqtt_dtp_t dtp = mqtt_make_topic_data_trace(server, NULL, MQTT_SEVEN_DAYS);
    
    REQUIRE(dtp.mqtt_logging_last_error == mqtt_success);
    
    mqtt_trace_data_turnOff(&dtp);

    REQUIRE(dtp.isON == 0);

    REQUIRE(mqtt_error_trace_turned_off == mqtt_tdt_published(&dtp, "/Test_Data_Trace_Root/Topic_Name_Data_Trace", 1, "jlkerlkjqew.213213edasaaaa"));

    REQUIRE(mqtt_error_trace_turned_off == mqtt_tdt_received(&dtp, "/Test_Data_Trace_Root/Topic_Name_Data_Received", 2, "kf;sdlkfw3wdnnddww/s33 wdsllwe3322 !@$^&&*(*&"));

    SECTION("ensure the file doesn't exists")
    {
       std::ifstream p_file("DATA-ONOFF_MessageData_01.log", std::fstream::in | std::fstream::binary);
       REQUIRE(!p_file.is_open());
    }

    mqtt_trace_data_turnOn(&dtp);

    REQUIRE(mqtt_success == mqtt_tdt_published(&dtp, "/Test_Data_Trace_Root/Topic_Name_Data_Trace", 1, "jlkerlkjqew.213213edasaaaa"));

    REQUIRE(mqtt_success == mqtt_tdt_received(&dtp, "/Test_Data_Trace_Root/Topic_Name_Data_Received", 2, "kf;sdlkfw3wdnnddww/s33 wdsllwe3322 !@$^&&*(*&"));


   SECTION("Check the file exists with the proper name and size and valid contents")
    {
        //Commands order is important , make it identical to API calls happened above.
        char const* commands[] = {"Published_data", "Received_data"};
        REQUIRE(mqtt_success == ValidateFile("DATA-ONOFF_MessageData_01.log", commands, 2));
    }
}


TEST_CASE("Session Trace File rolling , When file is old enough during tracing start")
{
    char server[] = "R1-SESSION";
    char time_stamp_filename[PATH_LENGTH];
    char filename[PATH_LENGTH];
    mqtt_time_t oldertime;

    if(mqtt_trace_getfilePath("", server, "ControlPacket", "timestamp", time_stamp_filename, PATH_LENGTH) == mqtt_success) {
        mqtt_pts_t pts;

        SECTION("Clean up any old files")
        {
            remove(time_stamp_filename);
            mqtt_trace_getfilePath("", server, "ControlPacket", "log", filename, PATH_LENGTH);
            remove(filename);
        }

        SECTION("Ensure to create the log file")
        {
            pts = mqtt_make_packet_trace_params(server, "", MQTT_SEVEN_DAYS);
            REQUIRE(pts.mqtt_logging_last_error == mqtt_success);

            REQUIRE(mqtt_success ==  mqtt_trace_packet_CONNECT(&pts, "BEFORE_ROLLING",  '1',  1,  0,  1,  2,  1,  0, 60,  "amhmekdkwe",  "Hello World",  "ahmedkorany@devfatory.com",  ""));
            
            SECTION("Override value in .timestamp file to simulate time pass")
            {
                remove(time_stamp_filename);
                oldertime = pts.file_creation_time - pts.file_rolling_period - 1;
                std::ofstream tmp_file(time_stamp_filename, std::fstream::out);
                tmp_file << std::setprecision(17) << oldertime;
                tmp_file.close();
            }
        }

        SECTION("Open file again and try to write somthing to it , test rolling")
        {
            pts = mqtt_make_packet_trace_params(server, "", MQTT_SEVEN_DAYS);
            REQUIRE(pts.mqtt_logging_last_error == mqtt_success);
            REQUIRE(mqtt_success ==  mqtt_trace_packet_CONNECT(&pts, "AFTER_ROLLING",  '1',  1,  0,  1,  2,  1,  0, 60,  "amhmekdkwe",  "Hello World",  "ahmedkorany@devfatory.com",  ""));
        }
        
        SECTION("Check if rolled file exists") {
            std::string backup_file_name;
            mqtt_trace_getfilePath("",server,"ControlPacket","old",filename,PATH_LENGTH);
            const char* commands[] = { "BEFORE_ROLLING" };
            REQUIRE(ValidateFile(filename, commands, 1) == mqtt_success);
        }
    }

}


TEST_CASE("Session Trace File rolling happens during tracing")
{
    char server[] = "R2-SESSION";
    int rolling = 5;

    SECTION("Clean up any old files")
    {
        remove("R2-SESSION_ControlPacket_01.log");
        remove("R2-SESSION_ControlPacket_01.timestamp");
    }
    SECTION("Start wrting to session trace file then sleep and write again")
    {
        mqtt_pts_t pts = mqtt_make_packet_trace_params(server, "", rolling);
        REQUIRE(pts.mqtt_logging_last_error == mqtt_success);

        REQUIRE(mqtt_success ==  mqtt_trace_packet_CONNECT(&pts, "BEFORE_ROLLING",  '1',  1,  0,  1,  2,  1,  0, 60,  "amhmekdkwe",  "Hello World",  "ahmedkorany@devfatory.com",  ""));
    
        std::cout << "Will Sleep " << rolling << " seconds to check rolling after that" << std::endl;
    
        msleep(rolling * SLEEP_FACTOR +1);

        REQUIRE(mqtt_success ==  mqtt_trace_packet_CONNECT(&pts, "AFTER_ROLLING",  '1',  1,  0,  1,  2,  1,  0, 60,  "amhmekdkwe",  "Hello World",  "ahmedkorany@devfatory.com",  ""));

        SECTION("Check the file exists with the proper name and valid contents")
        {
            //Commands order is important , make it identical to API calls happened above.
            char const* commands_after[] = {"AFTER_ROLLING"};
            REQUIRE(mqtt_success == ValidateFile("R2-SESSION_ControlPacket_01.log", commands_after, 1));

            //Commands order is important , make it identical to API calls happened above.
            char const* commands_before[] = {"BEFORE_ROLLING"};
            REQUIRE(mqtt_success == ValidateFile("R2-SESSION_ControlPacket_01.old", commands_before, 1));
        }
    }

}


TEST_CASE("Data Trace File rolling")
{
    char server[] = "R1-DATA";
    char time_stamp_filename[PATH_LENGTH];
    char filename[PATH_LENGTH];
    mqtt_time_t oldertime;

    if(mqtt_trace_getfilePath("", server, "MessageData", "timestamp", time_stamp_filename,PATH_LENGTH) == mqtt_success) {

        mqtt_dtp_t dtp;

        SECTION("Clean up any old files")
        {
            remove(time_stamp_filename);

            mqtt_trace_getfilePath("",server,"MessageData","log",filename,PATH_LENGTH);

            remove(filename);
        }

        SECTION("Ensure to create the log file")
        {
            dtp = mqtt_make_topic_data_trace(server, "", MQTT_SEVEN_DAYS);
            REQUIRE(dtp.mqtt_logging_last_error == mqtt_success);

            REQUIRE(mqtt_success == mqtt_tdt_published(&dtp, "/Test_Data_Trace_Root/BEFORE_ROLLING", 1, "jlkerlkjqew.213213edasaaaa"));
            
            SECTION("Override value in.timestamp file to simulate time pass")
            {
                oldertime = dtp.file_creation_time- dtp.file_rolling_period - 1;
                std::ofstream tmp_file(time_stamp_filename, std::fstream::out);
                tmp_file << std::setprecision(17) << oldertime;
                tmp_file.close();
            }
        }

        SECTION("Open file again and try to write somthing to it , test rolling")
        {
            dtp = mqtt_make_topic_data_trace(server, "", MQTT_SEVEN_DAYS);
            REQUIRE(dtp.mqtt_logging_last_error == mqtt_success);

            REQUIRE(mqtt_success == mqtt_tdt_published(&dtp, "/Test_Data_Trace_Root/AFTER_ROLLING", 1, "jlkerlkjqew.213213edasaaaa"));
        }
        
        SECTION("Check if rolled file exists") {

            std::string backup_file_name;
            std::stringstream string_stream;
            int dotIdx = (int)std::string(time_stamp_filename).find_last_of('.');
            std::string tmp_str(time_stamp_filename, dotIdx);
            const char* commands[] = { "BEFORE_ROLLING" };
            char date[28];

            time_t current_time = time(NULL);
            mqtt_ctime_s(&current_time, date, 28);
            replaceInvalidPathChar(date);
            string_stream << tmp_str << ".old";
            backup_file_name = string_stream.str();
            
            REQUIRE(ValidateFile(backup_file_name.c_str(),commands, 1) == mqtt_success);
        }
    }
}


TEST_CASE("Data Trace File rolling happens during trace time")
{
    char server[] = "R2-DATA";
    int rolling = 5;

    SECTION("Clean up any old files")
    {
        remove("R2-DATA_MessageData_01.log");
        remove("R2-DATA_MessageData_01.timestamp");
    }

    SECTION("Start wrting to data trace file then sleep and write again")
    {
        mqtt_dtp_t dtp = mqtt_make_topic_data_trace(server, "", rolling);
        REQUIRE(dtp.mqtt_logging_last_error == mqtt_success);

        REQUIRE(mqtt_success == mqtt_tdt_published(&dtp, "/Test_Data_Trace_Root/BEFORE_ROLLING", 1, "jlkerlkjqew.213213edasaaaa"));

        std::cout << "Will Sleep " << rolling << " seconds to check rolling after that" << std::endl;
    
        msleep(rolling * SLEEP_FACTOR +1);
    
        REQUIRE(mqtt_success == mqtt_tdt_published(&dtp, "/Test_Data_Trace_Root/AFTER_ROLLING", 1, "jlkerlkjqew.213213edasaaaa"));

        SECTION("Check the file exists with the proper name and valid contents")
        {
            //Commands order is important , make it identical to API calls happened above.
            char const* commands_after[] = {"AFTER_ROLLING"};
            REQUIRE(mqtt_success == ValidateFile("R2-DATA_MessageData_01.log", commands_after, 1));

            //Commands order is important , make it identical to API calls happened above.
            char const* commands_before[] = {"BEFORE_ROLLING"};
            REQUIRE(mqtt_success == ValidateFile("R2-DATA_MessageData_01.old", commands_before, 1));
        }
    }
}