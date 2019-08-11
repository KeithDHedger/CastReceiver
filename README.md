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
       castreceiver [OPTIONS]

   OPTIONS
       -V, --version
              Output version information and exit

       -f, --friendly-name
              Friendly name to advertise.

       -e, --exit-on-stop
              Exit when file stopped.

       -p, --player-command
                 Custom player command.
                 The default is to use the RPI3 omxplayer ( omxplayer --key-config ~/.config/omxkey.config ).

       -v, --verbose
                 Show renderer details on start.

       -h, --help
              Show help options

   EXAMPLES
       Set friendly name and use mplayer.
       castreceiver -f cast$(date +%M%S) --exit-on-stop -v -p mplayer

       Set friendly name and use mplayer on the framebuffer.
       castreceiver -f cast$(date +%M%S) --exit-on-stop -v -p "mplayer -vo fbdev2 -vf scale=1920:1019"

       Use default name and default player, keep going when cast video stops.
       castreceiver

BUGS ETC
       Bugs, feature requests, Large bags of jewels to:

       keithdhedger@gmail.com
