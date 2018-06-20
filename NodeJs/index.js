// to generate ssl : https://mosquitto.org/man/mosquitto-tls-7.html
//
// test cmd : 
// mosquitto_pub --cafile ssl/ca.crt --key ssl/client.key --cert ssl/client.crt -h 127.0.0.1 -t "test" -m "$(date)" -p 8883 --insecure
const port = 4000;
const portMQTT = 1883;
const portMQTT_S = 8883;

const mosca = require('mosca');
const fs = require('fs');
const express = require('express');

var app = express();
var server = require('http').createServer(app).listen ( port );
var io = require('socket.io').listen(server);

app.use ( express.static ( __dirname + '/public' ) );


const SECURE_KEY = __dirname + '/../ssl/server.key';
const SECURE_CERT = __dirname + '/../ssl/server.crt';


var settings = {
	stats: false,
	port:portMQTT,
	logger: {
		name: "secureExample",
		level: 40,
	},
	persistence: {
		factory: mosca.persistence.Memory
	},
	secure: { 
		port: portMQTT_S,
		keyPath: SECURE_KEY,
		certPath: SECURE_CERT,
	}
};

var serverMosca = new mosca.Server(settings);

console.log( "web server listening on " + port );

// web server part
app.get ( '/', function ( req, res )
{
	if ( settings.secure && 
		settings.secure.port )
	{
		res.render ( 'index.ejs', {dir:__dirname,port:settings.secure.port,secure:true} );
	}
	else if ( settings.port )
	{
		res.render ( 'index.ejs', {dir:__dirname,port:settings.port,secure:false} );
	}
});

app.use ( function ( err, req, res, next )
{
	console.log( "error : " + err.stack );
	res.statusCode = 404;
});

// MQTT server part
serverMosca.on('ready', function  ( )
{
	console.log('Mosca server is up and running');

	if ( settings.secure && 
		settings.secure.port )
	{
		console.log ( "MQTT secured listening on " + settings.secure.port );
	}
	else if ( settings.port )
	{
		console.log ( "MQTT unsecured listening on " + settings.port );
	}
});

serverMosca.on('clientConnected', function ( client )
{
	console.log('MQTT: '+client.id+' connected');
});

serverMosca.on('published', function ( data )
{
	// console.log( '--' + data.topic );
	// console.log( '  ' + data.payload );

	io.sockets.emit ( data.topic, data.payload + '' );
});

// IO socket server part
io.on('connection', function(client)
{
	console.log('IO: Client connected...');
});
