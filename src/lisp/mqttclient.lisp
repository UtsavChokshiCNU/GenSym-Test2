;;; This file calls functions in mqttclient code.

(defvar mqtt-context-handle 0)

;;; C function mapping for initializing context and sending CONNECT to broker
(def-gensym-c-function c-G2InitializeMQTTClientAndConnectToBroker
    (:pointer "G2InitializeMQTTClientAndConnectToBroker")
  ((:fixnum-int flags) ;; Flags contains clean-session, controlPacketLogging, messageDataLogging, lastWillRetain
   (:fixnum-int rollingLogsLimit)
   (:wide-string userName)
   (:wide-string password)
   (:wide-string lastWillTopic)
   (:fixnum-int lastWillQos)
   (:wide-string lastWillMessage)
   (:fixnum-int keepAlive)))

;;; system procedure for KB level
(defun-for-system-procedure kb-G2InitializeMQTTClientAndConnectToBroker (flags rollingLogsLimit 
		userName password lastWillTopic lastWillQos lastWillMessage keepAlive)
	(setf mqtt-context-handle 
		(c-G2InitializeMQTTClientAndConnectToBroker flags rollingLogsLimit userName password lastWillTopic 
			lastWillQos lastWillMessage keepAlive)))

(def-gensym-c-function c-G2ConnectToBroker
    (:pointer "G2ConnectToBroker")
  ((:pointer handle)
   (:fixnum-int flags) ;; Flags contains cleanSession, lastWillRetain
   (:wide-string userName)
   (:wide-string password)
   (:wide-string lastWillTopic)
   (:fixnum-int lastWillQos)
   (:wide-string lastWillMessage)
   (:fixnum-int keepAlive)))

;;; system procedure for KB level
(defun-for-system-procedure kb-G2ConnectToBroker (handle flags userName 
		password lastWillTopic lastWillQos lastWillMessage keepAlive)
	(c-G2ConnectToBroker handle flags userName password lastWillTopic 
		lastWillQos lastWillMessage keepAlive))

;;; C function mapping for setting broker logging properties
(def-gensym-c-function c-G2SetLoggingProperties
    (:pointer "G2SetLoggingProperties")
  ((:pointer handle)
   (:fixnum-int controlPacketLogging)
   (:fixnum-int messageDataLogging)
   (:fixnum-int rollingLogsLimit)))

;;; system procedure for KB level
(defun-for-system-procedure kb-G2SetLoggingProperties (handle controlPacketLogging messageDataLogging rollingLogsLimit)
	(c-G2SetLoggingProperties handle controlPacketLogging messageDataLogging rollingLogsLimit))

;;; C function mapping for receiving message from Broker
(def-gensym-c-function c-MqttPoll
    (:pointer "G2MqttPoll")
  ((:pointer handle)))
   
(defun-simple mqtt-poll-watcher ()
  (declare (eliminate-for-gsi))
  (c-MqttPoll mqtt-context-handle))

;;; C function mapping for publishing message to Broker
(def-gensym-c-function c-G2PublishToBroker
    (:pointer "G2PublishToBroker")
  ((:pointer handle)
   (:fixnum-int packetId)
   (:wide-string topicName)
   (:fixnum-int qos)
   (:fixnum-int retainFlag)
   (:wide-string payload)
   (:fixnum-int dupFlag)))

;;; system procedure for KB level
(defun-for-system-procedure kb-G2PublishToBroker (handle packetId topicName qos retainFlag payload dupFlag)
  (c-G2PublishToBroker handle packetId topicName qos retainFlag payload dupFlag))

;;; C function mapping for receiving message from Broker
(def-gensym-c-function c-G2DisconnectFromBroker
    (:pointer "G2DisconnectFromBroker")
  ((:pointer handle)))

;;; system procedure for KB level
(defun-for-system-procedure kb-G2DisconnectFromBroker (handle)
  (c-G2DisconnectFromBroker handle))