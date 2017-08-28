# MMM-HDC1080

This module shows the temperature and humidity of a HDC1080 Sensor by using the I2C of the RaspberryPi and displays it at your MagicMirror²  https://github.com/MichMich/MagicMirror


## Dependencies
- Enable your I2C of the RaspberryPi by going to Settings->RaspberryPi Configuration->interfaces->Enable I2C
- An installation of [MagicMirror<sup>2</sup>](https://github.com/MichMich/MagicMirror)
- [WiringPi] (http://wiringpi.com/download-and-install/)

## Installation

Navigate into your MagicMirror's `modules` folder:
```
cd ~/MagicMirror/modules
```

Clone this repository:
```
git clone https://github.com/Bangee44/MMM-DHT22
```

Navigate to the new `MMM-HDC1080` folder and make ReadHDC1080 executable.
```
cd MMM-HDC1080
chmod 755 ReadHDC1080
```

You can change the ReadHDC1080.c file for your own needs if you like to.
You'll have to recompile it using wirinpi lib.
```
cc -Wall ReadHDC1080.c -o ReadHDC1080 -lwiringPi
```

Configure the module in your `config.js` file.

## Using the module

To use this module, add it to the modules array in the `config/config.js` file:
```javascript
modules: [
  {
    module: 'MMM-HDC1080',
    position: 'top_right',
    config: {
            updateInterval: 0.5, // Minutes    
    },
  },
]
```

## Configuration options

The configuration options are still the same of https://github.com/Bangee44/MMM-DHT22

The following properties can be configured:

<table width="100%">
	<!-- why, markdown... -->
	<thead>
		<tr>
			<th>Option</th>
			<th width="100%">Description</th>
		</tr>
	<thead>
	<tbody>
		<tr>
			<td><code>sensorPIN</code></td>
			<td>GPIO PIN
        <br>
        <br>
        <b>Possible values:</b> wPi 
        <br>
				<b>Default value:</b> <code>2</code>
			</td>
		</tr>

    <tr>
			<td><code>updateInterval</code></td>
			<td>Updateinterval for DHT22 sensor in minutes
        <br>
        <b>Possible values:</b> int 
        <br>
				<b>Default value:</b> <code>0.5</code>
			</td>
		</tr>
	</tbody>
</table>
<br>
<p>
