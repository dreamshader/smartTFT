---


---

<h1 id="smarttft">smartTFT</h1>
<h2 id="brief-description">Brief description</h2>
<p>There is a lot of small and cheap color TFT displays around and with this project I want to give some of them the possibility to remotely control its content. Control is done by most common function calls of the Arduino GFX Library that are transferred to a µController that executes them.</p>
<h2 id="first-prototype">First Prototype</h2>
<p>First prototype is a 1.8" TFT with a ST7735 controller and additional SD-card slot.<br>
As a µController an Arduino Pro Mini is used.<br>
Communication is done using the UART of the Arduino.<br>
A self-made case will hold the components.<br>
A buzzer is used to realize an alarm-function, a LDR makes ist possible to change brightness of the display depending on ambient light.</p>
<p><em><strong>Be aware … this is a work-in-progress project. Some parts may not or not proper work. Use at your own risc!</strong></em></p>
<h2 id="parts-list-1st-prototype">Parts List 1st Prototype</h2>
<ul>
<li>1 x Arduino Pro Mini 1 x 1.8" TFT with SD-slot</li>
<li>2 x Levelshifter with 4 channels</li>
<li>1 x Stepup/Stepdown Regulator 5 &lt;-&gt; 3V3</li>
<li>1 x LDR</li>
<li>1 x Buzzer</li>
<li>1 x Resistor 10 kOhm</li>
<li>2 x Resistor 4.7 kOhm</li>
<li>1 x Resistor 100 Ohm</li>
<li>2 x Ceramic Capacitor 100 nF</li>
<li>1 x Proto-PCB 16 rows/32 columns (around 42 x 83 mm)</li>
<li>1 x Proto-PCB 16 rows/6 columns (around 42 x 15 mm)</li>
<li>1 x Stereo Jack female 3.5 mm</li>
<li>1 x DC Jack female 3.5 mm x 1.1 mm</li>
<li>1 x 4x1 Pin Header</li>
<li>a bunch of colored wires 0.14 mm</li>
</ul>
<h2 id="wiring-via-levelshifter">Wiring via Levelshifter</h2>

<table>
<thead>
<tr>
<th>Arduino</th>
<th>Levelshifter</th>
<th>Levelshifter</th>
<th>1.8" TFT</th>
</tr>
</thead>
<tbody>
<tr>
<td>Pin #10</td>
<td>HV*</td>
<td>LV**</td>
<td>TFT_CS</td>
</tr>
<tr>
<td>Pin #9</td>
<td>HV</td>
<td>LV</td>
<td>TFT_RST</td>
</tr>
<tr>
<td>Pin #8</td>
<td>HV</td>
<td>LV</td>
<td>TFT_DC</td>
</tr>
<tr>
<td>Pin #13</td>
<td>HV</td>
<td>LV</td>
<td>TFT_SCL</td>
</tr>
<tr>
<td>Pin #11</td>
<td>HV</td>
<td>LV</td>
<td>TFT_SDA</td>
</tr>
<tr>
<td>Pin #7</td>
<td>HV</td>
<td>LV</td>
<td>SD_CS</td>
</tr>
<tr>
<td>Pin #12</td>
<td>HV</td>
<td>LV</td>
<td>SD_MISO</td>
</tr>
<tr>
<td>Pin #11</td>
<td>HV</td>
<td>LV</td>
<td>SD_MOSI</td>
</tr>
<tr>
<td>Pin #13</td>
<td>HV</td>
<td>LV</td>
<td>SD_SCL</td>
</tr>
</tbody>
</table><p>*HV means High Voltage Side<br>
**LV means Low Voltage Side</p>
<hr>
<p>Because Vcc of the TFT is 5V <strong>be aware</strong> that <strong>Jumper J1</strong> on the back side of TFT is <strong>open!</strong> Otherwise the display is damaged.</p>
<h2 id="direct-wiring">Direct Wiring</h2>

<table>
<thead>
<tr>
<th>Arduino</th>
<th>Target 1</th>
<th>Target 2</th>
<th>is for</th>
</tr>
</thead>
<tbody>
<tr>
<td>Pin #5</td>
<td>100 Ohm</td>
<td>buzzer</td>
<td>limit current</td>
</tr>
<tr>
<td>Pin #6</td>
<td>TFT LED+</td>
<td>–</td>
<td>dim backlight</td>
</tr>
<tr>
<td>Pin A0</td>
<td>LDR</td>
<td>–</td>
<td>light sense</td>
</tr>
<tr>
<td>Pin A0</td>
<td>10 kOhm</td>
<td>GND</td>
<td>pulldown</td>
</tr>
</tbody>
</table><h2 id="realized-gfx-functions">Realized GFX-functions</h2>
<ul>
<li>drawLine()</li>
<li>drawFastHLine()</li>
<li>drawFastVLine()</li>
<li>drawRect()</li>
<li>fillRect()</li>
<li>drawCircle()</li>
<li>fillCircle()</li>
<li>drawTriangle()</li>
<li>fillTriangle()</li>
<li>drawRoundRect()</li>
<li>fillRoundRect()</li>
<li>setRotation()</li>
<li>setTextWrap()</li>
<li>fillScreen()</li>
<li>setTextColor()</li>
<li>fillScreen()</li>
<li>invertDisplay()</li>
<li>drawCircleHelper()</li>
<li>fillCircleHelper()</li>
<li>drawBitmap()</li>
<li>drawChar()</li>
<li>setCursor()</li>
<li>setTextSize()</li>
<li>height()</li>
<li>width()</li>
<li>write()</li>
<li>drawPixel()</li>
<li>print()</li>
<li>println()</li>
</ul>
<p>and. last but not least,</p>
<ul>
<li>setbrightness()</li>
</ul>
<p>for dimming backlight of the TFT Display.</p>

