// ------------------------------------------------ //
// Simple PoC for using 'libmosquitto'              // 
// https://mosquitto.org/api/files/mosquitto-h.html //
//                                                  //
// Usage: $ ./mosq_mqtt_sub [TOPIC]                 //
// ------------------------------------------------ //

#include <stdio.h>
#include <stdlib.h>
#include <mosquitto.h>

#define ID             "XFjRwHZlOBYWjJez-sub"
#define BROKER_HOST    "test.mosquitto.org"
#define BROKER_PORT    1883
#define BROKER_USER    NULL
#define BROKER_PASS    NULL

void on_connect(struct mosquitto *mosq, void *custom_data, int rc);
void on_message(struct mosquitto *mosq, void *custom_data, const struct mosquitto_message *msg);
void on_disconnect(struct mosquitto *mosq, void *custom_data, int rc);

int main(int argc, char *argv[]) {
	mosquitto_lib_init();

	if (argc != 2) {
		printf("@got_error 'wrong topic format given'\n");
		return 1;
	}
	
	char *custom_data = argv[1];
	struct mosquitto *mosq = mosquitto_new(ID, true, custom_data);

	mosquitto_connect_callback_set(mosq, on_connect);
	mosquitto_message_callback_set(mosq, on_message);
	mosquitto_disconnect_callback_set(mosq, on_disconnect);
	mosquitto_username_pw_set(mosq, BROKER_USER, BROKER_PASS);

	int rc = mosquitto_connect(mosq, BROKER_HOST, BROKER_PORT, 60);
	if (rc) {
		printf("@got_error 'could not connect to broker with code %d'\n", rc);
		return 1;
	}

	mosquitto_loop_start(mosq);
	printf("Press Enter to quit...\n");
	getchar();
	mosquitto_loop_stop(mosq, true);

	mosquitto_disconnect(mosq);
	mosquitto_destroy(mosq);
	mosquitto_lib_cleanup();

	return 0;
}

// ----------------------------------------------------------------------------
// Helpers
// ----------------------------------------------------------------------------

void on_connect(struct mosquitto *mosq, void *custom_data, int rc) {
	printf("on_connect 'to %s'\n", BROKER_HOST);
	
	if (rc) {
		printf("@got_error 'with result code: %d'\n", rc);
		exit(1);
	}

	char * sub_topic = (char *) custom_data;
	
	printf("@sub_topic '%s'\n", sub_topic);
	mosquitto_subscribe(mosq, NULL, sub_topic, 0);
}

void on_message(struct mosquitto *mosq, void *custom_data, const struct mosquitto_message *msg) {
	printf("on_message '%s' '%s'\n", msg->topic, (char *) msg->payload);
}

void on_disconnect(struct mosquitto *mosq, void *custom_data, int rc) {
	printf("on_disconnect 'reason %d'\n", rc);
}
