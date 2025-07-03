/* See LICENSE file for copyright and license details.
 * You will need a Nerd Font installed to see the icons */

/* interval between updates (in ms) */
const unsigned int interval = 1000;

/* text to show if no value can be retrieved */
static const char unknown_str[] = "n/a";

/* maximum output string length */
#define MAXLEN 2048

/*
 * function            description                     argument (example)
 *
 * battery_perc        battery percentage              battery name (BAT0)
 * battery_remaining   battery remaining HH:MM         battery name (BAT0)
 * battery_state       battery charging state          battery name (BAT0)
 * cpu_freq            cpu frequency in MHz            NULL
 * cpu_perc            cpu usage in percent            NULL
 * datetime            date and time                   format string (%F %T)
 * disk_free           free disk space in GB           mountpoint path (/)
 * disk_perc           disk usage in percent           mountpoint path (/)
 * disk_total          total disk space in GB          mountpoint path (/)
 * disk_used           used disk space in GB           mountpoint path (/)
 * entropy             available entropy               NULL
 * hostname            hostname                        NULL
 * ipv4                IPv4 address                    interface name (eth0)
 * ipv6                IPv6 address                    interface name (eth0)
 * kernel_release      `uname -r`                      NULL
 * keyboard_indicators caps/num lock indicators        format string (c?n?) see keyboard_indicators.c
 * load_avg            load average                    NULL
 * netspeed_rx         receive network speed           interface name (wlan0)
 * netspeed_tx         transfer network speed          interface name (wlan0)
 * ram_free            free memory in GB               NULL
 * ram_perc            memory usage in percent         NULL
 * ram_total           total memory size in GB         NULL
 * ram_used            used memory in GB               NULL
 * run_command         custom shell command            command (echo foo)
 * temp                temperature in degree celsius   sensor file (/sys/class/thermal/...)
 * uptime              system uptime                   NULL
 * wifi_essid          WiFi ESSID                      interface name (wlan0)
 * wifi_perc           WiFi signal in percent          interface name (wlan0)
 */

static const char vol[] = "muted=`wpctl get-volume @DEFAULT_SINK@ | awk '{print $3;}'`; \
                           volume=`wpctl get-volume @DEFAULT_SINK@ | awk '{print $2;}'`; \
                           if [ -z ${muted} ]; then \
                                printf \"${volume}\"; \
                           else printf \" \"; \
                           fi";

static const char vpn[] = "if [ $(cat /sys/class/net/tun0/operstate) = 'unknown' ]; then \
                           printf \"󰦝\"; \
                           else printf \"󰯆 \"; \
                           fi";

static const struct arg args[] = {
	/* function format          argument */
	{ keyboard_indicators,   "^c#00ff00^ %s ",  "C?N?" },
    { run_command,  "^c#bf616a^ ^b#000000^%s",             "echo " },
	{ cpu_perc,     "^b#bf616a^ ^c#000000^󰌢 %s%%",        NULL },
// 	{ run_command,  "^b#bf616a^ ^c#000000^%s",          "echo $(sensors | grep CPU | awk '{print $2}')" },
    { run_command,  "^c#d08770^ ^b#bf616a^%s",             "echo " },
   	{ ram_used,     "^b#d08770^ ^c#000000^ %s",        NULL },
    { run_command,  "^c#ebcb8b^ ^b#d08770^%s",             "echo " },
	{ wifi_perc,	"^b#ebcb8b^ ^c#000000^ %s%%",       "wlp2s0"},
	{ run_command,  "^b#ebcb8b^ ^c#000000^%2s" ,         vpn },
    { run_command,  "^c#a3be8c^ ^b#ebcb8b^%s",             "echo " },
	{ run_command,  "^b#a3be8c^ ^c#000000^ %2s",         vol },
    { run_command,  "^c#81A1C1^ ^b#a3be8c^%s",             "echo " },
	{ battery_state,"^b#81A1C1^ ^c#000000^%s",          "BAT0" },
	{ battery_perc,	"^b#81A1C1^ ^c#000000^%s%%",        "BAT0" },
//    { battery_remaining, "^b#81A1C1^ ^c#000000^%s",      "BAT0" },
    { run_command,  "^c#b48ead^ ^b#81A1C1^%s",             "echo " },
//	{ datetime, 	"^b#b48ead^ ^c#000000^%2s",           " %a %e %B" },
	{ datetime,     "^b#b48ead^ ^c#000000^%s",           "󰥔 %T" },
    { run_command,  "^c#000000^ ^b#b48ead^%s",             "echo " },
};
