#include <mosquitto.h>
#include <stdbool.h>
#include <stdio.h>

// to install mosquitto :
// git clone https://github.com/eclipse/mosquitto.git
// make
// make install

bool ackDone = false;

static void disconnectCallback ( struct mosquitto * restrict mosq, void * restrict obj, int result )
{
}
static void publishCallback ( struct mosquitto * restrict mosq, void * restrict obj, int result )
{
}
static void connectCallback ( struct mosquitto * restrict mosq, void * restrict obj, int result )
{
	if ( !result )
	{
		ackDone = true;
	}
	else if ( result )
	{
		fprintf ( stderr, "%s\n", mosquitto_connack_string ( result ) );
	}
}

int main ( void )
{
	const int port = 8883;
	const char host[] = "127.0.0.1";
	const char ca[] = "../ssl/ca.crt";
	const char cert[] = "../ssl/client.crt";
	const char key[] = "../ssl/client.key";
	struct mosquitto * mosq;
	int value = 0;
	int arg = 0;

	static int id = 0;

	if ( mosquitto_lib_init( ) )
	{
		return ( __LINE__ );
	}
	mosq = mosquitto_new ( "C_soft", true, NULL );

	if ( !mosq )
	{
		return ( __LINE__ );
	}


	mosquitto_connect_callback_set ( mosq, connectCallback );
	mosquitto_disconnect_callback_set ( mosq, disconnectCallback );
	mosquitto_publish_callback_set ( mosq, publishCallback );

	if ( mosquitto_will_set ( mosq, "/data", 16, "C client stoped", 0, 0 ) )
	{
		return ( __LINE__ );
	}

	if ( mosquitto_tls_opts_set ( mosq, 1, NULL, NULL ) ||
		mosquitto_tls_set ( mosq, ca, NULL, cert, key, NULL ) ||
		mosquitto_tls_insecure_set ( mosq, true ) )
	{
		return ( __LINE__ );
	}

	value = MQTT_PROTOCOL_V31;
	if ( mosquitto_max_inflight_messages_set ( mosq, 20 ) ||
	 mosquitto_opts_set ( mosq, MOSQ_OPT_PROTOCOL_VERSION, &value ) )
	{
		return ( __LINE__ );
	}
	value = 0;

	if ( mosquitto_connect ( mosq, host, port, 1000000 ) )
	{
		return ( __LINE__ );
	}

	while ( ackDone == false )
	{
		value = mosquitto_loop ( mosq, -1, 1 );
		if ( value )
		{
			printf ( "%d : %s\n", __LINE__, mosquitto_strerror ( value ) );
			return ( __LINE__ );
		}
		else
		{
			usleep ( 50000 );
		}
	}

	mosquitto_publish ( mosq, &id, "/data", 6, "C msg", 0, 0 );

	mosquitto_destroy ( mosq );
	mosquitto_lib_cleanup ( );

	return ( 0 );
}