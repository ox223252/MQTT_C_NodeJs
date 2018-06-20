# MQTT / C / Node js

This is an example of how to build a project using a **MQTT** server over **NoeJs** with **C** software.

## Usage:

### Test MQTT broker:

```shell
~/MQTT_C_NodeJs/ > sudo apt-get install mosquitto mosquitto_pub npm nodejs
~/MQTT_C_NodeJs/ > ./genKey.sh
...
~/MQTT_C_NodeJs/ > cd Nodejs
~/MQTT_C_NodeJs/NodeJs > npm install
~/MQTT_C_NodeJs/NodeJs > js index.js
web server listening on 4000
Mosca server is up and running
...
```

Open a webBrowser and got to the server web page, copy / past the displayed cmd to a new term, that should work.

### Test C publisher:



## SSL:

If you want to use SSL/TSL encryption for your software use **./genKey.sh**.

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

You should customize the key gen by changin this vars:

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

If this part is commented, the server will work without **SSL / TLS** encryption, esle it'll work with that.

Before try to work with SSL you should generate keys.

The default page of this server will display the availables commandes what you can use for tests prupose.


