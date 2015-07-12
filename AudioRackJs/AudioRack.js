var app = require('http').createServer(handler);
var io = require('socket.io').listen(app);
var fs = require('fs');
var bone = require('bonescript');
var ipc = require('node-ipc');

ipc.config.id = 'AudioRack';
ipc.config.retry = 1000;
ipc.config.appspace = '';
ipc.config.socketRoot = '';

ipc.connectTo('DEP_audio_rack', '/tmp/DEP_audio_rack', function() {
});

var backlight_output = "P8_13";
var contrast_output = "P8_19";

bone.pinMode(backlight_output, bone.ANALOG_OUTPUT);
bone.pinMode(contrast_output, bone.ANALOG_OUTPUT);

bone.analogWrite(backlight_output, 0.5 , 2000, printError);
bone.analogWrite(backlight_output, 0.5 , 2000, printError);

app.listen(8090);

function handler (req, res) {
    switch(req.url) {
        case "/LCD_controls":
            file = 'InterfaceLCD.html';
            break;
        case "/AudioRackStyle.css":
            file = 'AudioRackStyle.css';
            break;
        case "/About":
            file = 'AboutDEP.html';
            break;
        default:
            file = 'AudioRack.html';
    }
    fs.readFile(file,
    function (err, data) {
        if (err) {
            res.writeHead(500);
            return res.end('Error loading ' + file);
        }
        res.writeHead(200);
        res.end(data);
  });
}


 
io.sockets.on('connection', function (socket) {
    socket.on('gain', function(data) {
        ipc.of.DEP_audio_rack.emit('gain', data); 
    });
    socket.on('psaturation', function(data) {
        ipc.of.DEP_audio_rack.emit('psaturation', data); 
    });
    socket.on('nsaturation', function(data) {
        ipc.of.DEP_audio_rack.emit('nsaturation', data);
    });
    socket.on('decay', function(data) {
        ipc.of.DEP_audio_rack.emit('decay', data); 
    });
    socket.on('delay', function(data) {
        ipc.of.DEP_audio_rack.emit('delay', data); 
    });
    socket.on('eq_0', function(data) {
        ipc.of.DEP_audio_rack.emit('eq_0', data); 
    });
    socket.on('eq_1', function(data) {
        ipc.of.DEP_audio_rack.emit('eq_1', data); 
    });
    socket.on('eq_2', function(data) {
        ipc.of.DEP_audio_rack.emit('eq_2', data); 
    });
    socket.on('eq_3', function(data) {
        ipc.of.DEP_audio_rack.emit('eq_3', data); 
    });
    socket.on('eq_4', function(data) {
        ipc.of.DEP_audio_rack.emit('eq_4', data); 
    });
    socket.on('eq_5', function(data) {
        ipc.of.DEP_audio_rack.emit('eq_5', data); 
    });
    socket.on('eq_6', function(data) {
        ipc.of.DEP_audio_rack.emit('eq_6', data); 
    });
    socket.on('eq_7', function(data) {
        ipc.of.DEP_audio_rack.emit('eq_7', data); 
    });
    socket.on('backlight_pwm', function(data) {
        bone.analogWrite(backlight_output, data/100 , 2000, printError);
    });
    socket.on('contrast_pwm', function(data) {
        bone.analogWrite(contrast_output, data/100 , 2000, printError);
    });
    socket.on('lcd_message', function(data) {
        console.log(data);
        //ipc.of.lcd_socket.emit('app.message', data);
    });
});
 
function printError(x) {
  console.log('PWM ne radi: ' + JSON.stringify(x));
}
