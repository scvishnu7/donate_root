#include <linux/module.h>
#include <linux/sched.h>
#include <linux/cred.h>
#include <linux/slab.h>

static int pid;

void print_cred(struct cred mycred ) {
printk("====== Printing cred =====\n");
printk(" uid = %d \n gid = %d\n", mycred.uid, mycred.gid);
printk(" suid = %d\n sgid = %d\n", mycred.suid, mycred.sgid);
printk(" euid = %d\n egid = %d\n", mycred.euid, mycred.egid);
printk(" fsuid = %d\n fsgid = %d\n", mycred.fsuid, mycred.fsgid);
}

int init_module(void) {
	struct task_struct *task;
	struct cred *new_cred;

	printk("Lets search that pid supplied\n");
	for_each_process(task) {
		if(task->pid == pid)
			break;
	}
	printk("The task to be given root is  %s:%d\n",task->comm, task->pid);
	new_cred = (struct cred *)kmalloc(sizeof(struct cred), GFP_KERNEL);

	memcpy(new_cred, task->real_cred, sizeof(struct cred));

	new_cred->uid = 0;// making it root
	new_cred->gid = 0;
	new_cred->suid = 0;
	new_cred->sgid = 0;
	new_cred->euid = 0;
	new_cred->egid = 0;
	new_cred->fsuid = 0;
	new_cred->fsgid = 0;

	print_cred(*new_cred);
	print_cred(*(task->real_cred));


	memcpy(task->real_cred, new_cred, sizeof(struct cred));

	return 0;
}

void cleanup_module(void) {
	printk("Good bye World !\n");
}

module_param(pid,int ,1);
MODULE_PARM_DESC(pid,"Pid of process to be rooted");

MODULE_LICENSE("GPL");
