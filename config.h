/* See LICENSE file for copyright and license details. */

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
                            else printf \"MUTED\"; \
                            fi";

static const char vpn[] = "if [ $(cat /sys/class/net/tun0/operstate) = 'unknown' ]; then \
                           printf \"\"; \
                           else printf \" \"; \
                           fi";

static const struct arg args[] = {
	/* function format          argument */
	{ keyboard_indicators,   "^c#00ff00^ %s",  "C?" },
	{ cpu_perc,     "^c#a42eff^  %s%%",        NULL }, // fc0000
 	{ run_command,  "^c#a42eff^ %2s ",          "echo $(sensors | grep CPU | awk '{print $2}')" }, // fc0000
   	{ ram_used,     "^c#a42eff^  %2s ",        NULL }, // ffa500
	{ wifi_perc,	"^c#a42eff^  %2s%%",       "wlan0"}, // ffef00
	{ run_command,  "^c#00fcfc^ %2s " ,         vpn }, // ffef00
	{ run_command,  "^c#a42eff^   %2s",         vol }, // 00ff00
	{ battery_state,"^c#a42eff^ %2s",          "BAT0" }, // 0000fc
	{ battery_perc,	"^c#a42eff^ %2s%%",        "BAT0" }, // 0000fc
	{ datetime, 	"^c#FFFFFF^ %2s",           "%a, %e %B %y" },
	{ datetime,     "^c#FFFFFF^ %2s",           " %T " },
};
