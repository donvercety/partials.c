// ------------------------------------------------ //
// Simple PoC for using 'libmosquitto'              // 
// https://mosquitto.org/api/files/mosquitto-h.html //
//                                                  //
// Usage: $ ./mosq_mqtt_pub [TOPIC] [MSG]           //
//                                                  //
// Current state:                                   //
// - pub "broker.hivemq.com"   fails, no errors     //
// - pub "test.mosquitto.org"  OK                   //
// - pub "mqtt.fluux.io"       OK                   //
// ------------------------------------------------ //

#include <stdio.h>
#include <string.h>
#include <mosquitto.h>

#define ID             "XFjRwHZlOBYWjJez-pub"
#define BROKER_HOST    "test.mosquitto.org"
#define BROKER_PORT    1883
#define BROKER_USER    NULL
#define BROKER_PASS    NULL

int main(int argc, char *argv[]){
	if (argc != 3) {
		printf("@got_error 'wrong topic or message format given'\n");
		return 1;
	}

	mosquitto_lib_init();

	struct mosquitto *mosq = mosquitto_new(ID, true, NULL);
	mosquitto_username_pw_set(mosq, BROKER_USER, BROKER_PASS);

	int rc = mosquitto_connect(mosq, BROKER_HOST, BROKER_PORT, 60);
	if (rc != 0){
		printf("@got_error 'could not connect to broker with code %d'\n", rc);
		mosquitto_destroy(mosq);
		return 1;
	}

	printf("@connected 'to %s'\n", BROKER_HOST);

	int msg_bytes = strlen(argv[2]);

	printf("@pub_topic '%s' '%s' '%d'\n", argv[1], argv[2], msg_bytes);
	rc = mosquitto_publish(mosq, NULL, argv[1], msg_bytes, argv[2], 0, false);
	printf("@pub_rcval '%d'\n", rc);

	mosquitto_disconnect(mosq);
	mosquitto_destroy(mosq);
	mosquitto_lib_cleanup();

	return 0;
}
