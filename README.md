# MQTT / C / Node js

This is an example of how to build a project using a **MQTT** server over **Node Js** with **C** software.

## Usage:

### Test MQTT broker:

```shell
~/MQTT_C_NodeJs > sudo apt-get install npm nodejs
~/MQTT_C_NodeJs > ./genKey.sh
...
~/MQTT_C_NodeJs > cd Nodejs
~/MQTT_C_NodeJs/NodeJs > npm install
~/MQTT_C_NodeJs/NodeJs > js index.js
web server listening on 4000
Mosca server is up and running
...
```

Open a web browser and go to the server web page, copy / paste the displayed cmd to a new term, that should work.

### Test C publisher:

```shell
~/MQTT_C_NodeJs > git clone https://github.com/eclipse/mosquitto.git
~/MQTT_C_NodeJs > make
~/MQTT_C_NodeJs > make install
~/MQTT_C_NodeJs > cd C
~/MQTT_C_NodeJs/C > ./Configure/config
~/MQTT_C_NodeJs/C > make
~/MQTT_C_NodeJs/C > ./bin/exec
```

The web page should add two msg to it's content:

```
C msg
C client stoped
```

On the Node Js term it should appear a new line:

```shell
MQTT: C_soft connected
```



## SSL:

If you want to use SSL/TLS encryption for your software use **./genKey.sh**.

### Usage:

```sh
 > ./genKey.sh
 GCA:
Generating a 2048 bit RSA private key
........................................+++
.............+++
writing new private key to 'ssl/ca.key'
Enter PEM pass phrase:
Verifying - Enter PEM pass phrase:
-----
 Server:
Generating RSA private key, 2048 bit long modulus
................................+++
.........................................................................................+++
e is 65537 (0x10001)
Signature ok
subject=/C=FR/ST=FR/O=MyComagny/OU=DevLabServer/CN=ox223252_server
Getting CA Private Key
Enter pass phrase for ssl/ca.key:
 Client:
Generating RSA private key, 2048 bit long modulus
.........................................................................................+++
...........+++
e is 65537 (0x10001)
Signature ok
subject=/C=FR/ST=FR/O=MyComagny/OU=DevLabClient/CN=ox223252_client
Getting CA Private Key
Enter pass phrase for ssl/ca.key:
```

Inpired by [mosquitto](https://mosquitto.org/man/mosquitto-tls-7.html) explanations.

### Customize:

You should customize the keygen by changing this vars:

|                                   | C <br>(contry) | ST <br>(state) | L <br>'(city) | O <br>(organization) | OU <br>(organization unit) | CN <br>(comon name) |
| --------------------------------- | -------------- | -------------- | ------------- | -------------------- | -------------------------- | ------------------- |
| CA <br> (certification authority) | FR             | France         | Paris         | MyCompagny           | BE                         | Honoré              |
| SR <br> (server)                  | FR             | France         | Paris         | MyServerManager      | Data Admin                 | Michel              |
| CL <br> (client)                  | FR             | France         | Paris         | MyClient             | Data Prod                  | Robert              |



## MQTT over NodeJs:

By default the web server listening on port **4000**, and MQTT server listening **1883** or **8883** for normal or secure mode. 

You could change the mode by commenting a small part of code (lines 34 - 38).

```javascript
	secure: { 
		port: portMQTT_S,
		keyPath: SECURE_KEY,
		certPath: SECURE_CERT,
	}
```

If this part is commented, the server will work without **SSL / TLS** encryption, else it'll work with that.

Before try to work with SSL you should generate keys.

The default page of this server will display the available commands what you can use for tests purpose.



## MQTT ovec C:

By default this sender is configured to work with the given NodeJs server, and to send one message and a disconnection message.

If you want to work without SSL/TLS encryption you should comment line 64 to 69:

```c
if ( mosquitto_tls_opts_set ( mosq, 1, NULL, NULL ) ||
		mosquitto_tls_set ( mosq, ca, NULL, cert, key, NULL ) ||
		mosquitto_tls_insecure_set ( mosq, true ) )
	{
		return ( __LINE__ );
	}
```

and change port line 32:

```c
const int port = 8883;
```

to 

```c
const int port = 1883;
```

according to the Node Js broker.

Note that, if you whant to send multiple msg form differents part of a bigger code, you should add a tread with only one task, to execut periodicly *mosquitto_loop()* function, this function will keep the connection working.
