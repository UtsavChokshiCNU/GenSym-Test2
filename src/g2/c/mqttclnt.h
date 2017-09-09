/* mqttclnt.h -- Header File for mqttclnt.c
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */

extern Object Pclos;
extern Object Pclos_run;
extern Object Pclosx;
extern Object Pcl;
extern Object Pcl_user;
extern Object Pkeyword;
extern Object Ptrun;
extern Object Ptx;

/* function declarations */

#ifdef USE_PROTOTYPES

extern Object c_g2connecttobroker(Object,Object,Object,Object,Object,Object,Object,Object);
extern Object c_g2initializemqttclientandconnecttobroker(Object,Object,Object,Object,Object,Object,Object,Object);
extern Object c_g2publishtobroker(Object,Object,Object,Object,Object,Object,Object);
extern Object kb_g2connecttobroker(Object,Object,Object,Object,Object,Object,Object,Object);
extern Object kb_g2disconnectfrombroker(Object);
extern Object kb_g2initializemqttclientandconnecttobroker(Object,Object,Object,Object,Object,Object,Object,Object);
extern Object kb_g2publishtobroker(Object,Object,Object,Object,Object,Object,Object);
extern Object kb_g2setloggingproperties(Object,Object,Object,Object);
extern Object mqtt_poll_watcher(void);
extern Object mutate_global_property(Object,Object,Object);

#else

extern Object c_g2connecttobroker();
extern Object c_g2initializemqttclientandconnecttobroker();
extern Object c_g2publishtobroker();
extern Object kb_g2connecttobroker();
extern Object kb_g2disconnectfrombroker();
extern Object kb_g2initializemqttclientandconnecttobroker();
extern Object kb_g2publishtobroker();
extern Object kb_g2setloggingproperties();
extern Object mqtt_poll_watcher();
extern Object mutate_global_property();

#endif

/* variables/constants */
extern Object Mqtt_context_handle;
