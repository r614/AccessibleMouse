const {app, BrowserWindow} = require('electron');
var sp = require('serialport');

let win;

function createWindow() {
        win = new BrowserWindow({
        	width: 800, 
        	height: 600,
        	title: "Settings"
        });

        win.loadFile('index.html');

        sp.list(function(err, ports){
                console.log(ports);
        })

        win.on('closed', () => {
                win = null;
        })
}

app.on('ready', createWindow)

app.on('window-all-closed', () => {
        if (process.platform !== 'darwin'){
                app.quit();
        }
})

app.on('activate', () => {
        if (win === null) {
                createWindow();
        }
})