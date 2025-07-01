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
                           printf \"󱚿\"; \
                           else printf \"󰯆 \"; \
                           fi";

static const struct arg args[] = {
	/* function format          argument */
	{ keyboard_indicators,   "^c#00ff00^ %s ",  "C?N?" },
	{ cpu_perc,     "^c#bf616a^  %s%% ",        NULL },
// 	{ run_command,  "^c#bf616a^ %2s",          "echo $(sensors | grep CPU | awk '{print $2}')" },
   	{ ram_used,     "^c#d08770^  %2s ",        NULL },
	{ run_command,  "^c#ebcb8b^ %2s" ,         vpn },
	{ wifi_perc,	"^c#ebcb8b^ %2s%% ",       "wlp2s0"},
	{ run_command,  "^c#a3be8c^  %2s ",         vol },
	{ battery_state,"^c#81A1C1^ %2s",          "BAT0" },
	{ battery_perc,	"^c#81A1C1^ %2s%%",        "BAT0" },
    { battery_remaining, "^c#81A1C1^ %2s ",      "BAT0" },
	{ datetime, 	"^c#b48ead^ %2s",           " %a %e %B" },
	{ datetime,     "^c#b48ead^ %2s ",           "󰥔 %T" },
};
