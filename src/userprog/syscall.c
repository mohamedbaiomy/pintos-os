#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"

static void syscall_handler (struct intr_frame *);

static void sys_halt (void);
static int sys_exit (int);
static int sys_exec (const char *);
static int sys_wait (int);
static bool sys_create (const char *file, unsigned initial_size);
static bool sys_remove (const char *file);
static int sys_open (const char * file);
static int sys_filesize (int fd);
static int sys_read (int fd, void *buffer, unsigned size);
static int sys_write (int fd, const void *buffer, unsigned size);
static void sys_seek (int fd, unsigned position);
static unsigned int sys_tell (int fd);
static void sys_close (int fd);
  
void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler (struct intr_frame *f) 
{
  printf ("system call!\n");
  thread_exit ();

  int *syscall_number;
  int ret;
  
  syscall_number= f->esp;

  switch (*syscall_number) {

  case SYS_HALT:
    sys_halt();
    break;
  case SYS_EXIT:
    ret = sys_exit (*(syscall_number + 1));
    break;
  case SYS_EXEC:
    ret = sys_exec ((char *) *(syscall_number + 1));
    break;
  case SYS_WAIT:
    ret = sys_wait (*(syscall_number + 1));
    break;
  case SYS_REMOVE:
    ret = sys_remove (*(syscall_number + 1));
    break;
  case SYS_OPEN:
    ret = sys_open ((char *) *(syscall_number + 1));
    break;
  case SYS_FILESIZE:
    ret = sys_filesize (*(syscall_number + 1));
    break;
  case SYS_TELL:
    ret = sys_tell (*(syscall_number + 1));
    break;
  case SYS_CLOSE:
    sys_close (*(syscall_number + 1));
    break;
  case SYS_CREATE:
    ret = sys_create ((char *) *(syscall_number + 1), *(syscall_number + 2));
    break;
  case SYS_SEEK:
    sys_seek ((char *) *(syscall_number + 1), *(syscall_number + 2));
    break;
  case SYS_READ:
    ret = sys_read (*(syscall_number + 1), (void *)*(syscall_number + 2), *(syscall_number + 3));
    break;
  case SYS_WRITE:
    ret = sys_write (*(syscall_number + 1), (void *) *(syscall_number + 2), *(syscall_number + 3));
    break;
  default:
    break;
  }

  f->eax = ret;

  return;
}

static void sys_halt (void)
{
  power_off();
  return;
}

static int sys_exit (int status UNUSED)
{
  return 0;
}

static int sys_exec (const char * cmd_line UNUSED)
{
  return 0;
}

static int sys_wait (int pid UNUSED)
{
  return 0;
}

static bool create (const char *file UNUSED, unsigned initial_size UNUSED)
{
  return 0;
}

static bool sys_remove (const char *file UNUSED)
{
  return 0;
}

static int sys_open (const char * file UNUSED)
{
  return 0;
}

static int sys_filesize (int fd UNUSED)
{
  return 0;
}

static int sys_read (int fd UNUSED, void *buffer UNUSED, unsigned size UNUSED)
{
  return 0;
}

static int sys_write (int fd UNUSED, const void *buffer UNUSED, unsigned size UNUSED)
{
  return 0;
}

static void sys_seek (int fd UNUSED, unsigned position UNUSED)
{
  return;
}

static unsigned int sys_tell (int fd UNUSED)
{
  return 0;
}

static void sys_close (int fd UNUSED)
{
  return;
}
