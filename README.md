# CastReceiver

This Code is heavliy based on gmrender-resurrect, origiganl source can be found here:
https://github.com/hzeller/gmrender-resurrect

Code hase been cleaned and translated to c++

Tested on rpi3 + AllCast on android.

Still a number of bugs yet :( ...
...
More to come
...

Quick guide.

USAGE
       castreceiver OPTIONS


OPTIONS<br>
<br>
-V, --version<br>
       Output version information and exit<br>
<br>
-f, --friendly-name<br>
       Friendly name to advertise.<br>
<br>
-e, --exit-on-stop<br>
       Exit when file stopped.<br>
<br>
-p, --player-command<br>
       Custom player command.<br>
       The default is to use the RPI3 omxplayer ( omxplayer --key-config ~/.config/omxkey.config ).<br>
<br>
-v, --verbose<br>
       Show renderer details on start.<br>
<br>
-h, --help<br>
       Show help options<br>
<br>
EXAMPLES<br>
       Set friendly name and use mplayer.<br>
       castreceiver -f cast$(date +%M%S) --exit-on-stop -v -p mplayer<br>
<br>
       Set friendly name and use mplayer on the framebuffer.<br>
       castreceiver -f cast$(date +%M%S) --exit-on-stop -v -p "mplayer -vo fbdev2 -vf scale=1920:1019"<br>
<br>
       Use default name and default player, keep going when cast video stops.<br>
       castreceiver<br>
<br>
BUGS ETC<br>
       Bugs, feature requests, Large bags of jewels to:<br>
<br>
       keithdhedger@gmail.com
