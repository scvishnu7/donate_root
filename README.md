donate_root
===========

A LKM which when insmod'ed with pid of the target process, make that process run wit root privilege<br/>
<br/>
Do `make` and then 'sudo insmod rooter.ko pid=`<pid of target>`<br/>
After that the target will get root privilege.<br/>
As insmod can only be done by root, this LKM seems unuseful but i just love to see the `whoami` output as `root` when the prompt is still `$`.
