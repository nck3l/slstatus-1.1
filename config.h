/* See LICENSE file for copyright and license details.
 * You will need a Nerd Font installed to see the icons /

 * interval between updates (in ms) */
const unsigned int interval = 1000;

/* text to show if no value can be retrieved */
static const char unknown_str[] = "n/a";

/* maximum output string length */
#define MAXLEN 2048

static const char vol[] = "muted=`wpctl get-volume @DEFAULT_SINK@ | awk '{print $3;}'`; \
                           volume=`wpctl get-volume @DEFAULT_SINK@ | awk '{print(100 * $2);}'`; \
                           if [ -z ${muted} ]; then \
                                printf \"${volume}\"; \
                           else printf \" \"; \
                           fi";

static const char network[] =  "wire=`ip a | rg eth0 | rg inet | wc -l`; \
                            wifi=`ip a | rg wlan0 | rg inet | wc -l`; \
                            signal=`iwconfig wlan0 | awk -F\"[ =]+\" '/Quality/{print $4}')`; \
                            if [ $(cat /sys/class/net/tun0/operstate) = 'unknown' ]; then \
                                if [ ${wire} = 1 ]; then \
                                    printf \"󰯄 \"; \
                                elif [ ${wifi} = 1 ]; then \
                                    printf \"󱚿 ${signal}\"; \
                                fi \
                            else printf \"󰚌\"; \
                            fi";

static const struct arg args[] = {
	/* function format          argument */
	{ cpu_perc,     "^c#dc322f^󰻠 %s%%",           NULL },//BF616A
    { ram_used,     "^c#b58900^ 󰘚 %sB",           NULL },//EBCB8B
	{ run_command,  "^c#2aa198^ %2s" ,            network },//A3BE8C
	{ run_command,  "^c#268bd2^  %2s%%",         vol },//88C0D0
	{ battery_state,"^c#d33682^ %s",              "BAT0" },//B48EAD
    { battery_remaining, "^c#d33682^ %s",         "BAT0" },
	{ battery_perc,	"^c#d33682^ %s%%",            "BAT0" },
    { datetime, 	"^c#ffffff^ %2s",             "󰥔 %a %e %b %H:%M " },
};
