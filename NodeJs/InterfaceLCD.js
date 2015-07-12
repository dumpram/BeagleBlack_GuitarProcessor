var app = require('http').createServer(handler);
var io = require('socket.io').listen(app);
var fs = require('fs');
var bone = require('bonescript');
var ipc = require('node-ipc');

ipc.config.id = 'hello';
ipc.config.retry = 1000;
ipc.config.appspace = '';
ipc.config.socketRoot = '';

ipc.connectTo('lcd_socket', '../IPC/lcd_socket', function() {
});

var backlight_output = "P8_13";
var contrast_output = "P8_19";

bone.pinMode(backlight_output, bone.ANALOG_OUTPUT);
bone.pinMode(contrast_output, bone.ANALOG_OUTPUT);

app.listen(8090);


function printError(x) {
  console.log('PWM ne radi: ' + JSON.stringify(x));
}

function handler (req, res) {
  fs.readFile('InterfaceLCD.html',
  function (err, data) {
    if (err) {
      res.writeHead(500);
      return res.end('Error loading InterfaceLCD.html');
    }
    res.writeHead(200);
    res.end(data);
  });
}
 
io.sockets.on('connection', function (socket) {
  socket.on('backlight_pwm', function(data) {
    bone.analogWrite(backlight_output, data/100 , 2000, printError);
  });
  socket.on('contrast_pwm', function(data) {
    bone.analogWrite(contrast_output, data/100 , 2000, printError);
  });
  socket.on('lcd_message', function(data) {
    console.log(data);
    ipc.of.lcd_socket.emit('app.message', data);
    });
});
 
