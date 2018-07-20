#
# Regular cron jobs for the cards-500 package
#
0 4	* * *	root	[ -x /usr/bin/cards-500_maintenance ] && /usr/bin/cards-500_maintenance
