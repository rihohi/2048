#include "2048.h"
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <errno.h>

int buttons_fd;
char first_flag = 0;
/*
     64     32     16      8

     32     16      8      4

     16      8      4      2

      8      4      2      1

You die!
press <y> to play, <n> to quit

*/
char keyborad(){
	char buttons[2] = {'0', '0'};
	
	int i;
	char current_buttons[2];
	char realchar;

	if (read(buttons_fd, current_buttons, sizeof current_buttons) != sizeof current_buttons) {
		perror("read buttons:");
		exit(1);
	}
	if(first_flag == 0)
		first_flag = 1;
	else
	{
		if (buttons[0] != current_buttons[0] || buttons[1] != current_buttons[1]) 
		{
			buttons[0] = current_buttons[0];
			buttons[1] = current_buttons[1];
			switch(buttons[0])
			{
			case 51:
				switch(buttons[1])
				{
					case 51:realchar='1';break;
					case 50:realchar='2';break;
					case 49:realchar='3';break;
					case 48:realchar='A';break;
				}break;
			case 50:
				switch(buttons[1])
				{
					case 51:realchar='4';break;
					case 50:realchar='5';break;
					case 49:realchar='6';break;
					case 48:realchar='B';break;
				}break;
			case 49:
				switch(buttons[1])
				{
					case 51:realchar='7';break;
					case 50:realchar='8';break;
					case 49:realchar='9';break;
					case 48:realchar='C';break;
				}break;
			case 48:
				switch(buttons[1])
				{
					case 51:realchar='*';break;
					case 50:realchar='0';break;
					case 49:realchar='#';break;
					case 48:realchar='D';break;
				}break;
				printf("key(%c) is pressed!\n", realchar);
			}
		}
		
	}
	return realchar;	
}
int main()
{
	buttons_fd = open("/dev/dial_key", 0);
	if (buttons_fd < 0) {
		perror("open device buttons failed£¡");
		exit(1);
	}
	system("clear");
	init();
	
	show();
	
	char ch;

	
	//while((ch = getch_from_terminal()) != VK_QUIT)
	while(1)
	{
		ch = keyborad();
		switch(ch)
		{
			case '2':
				handle(VK_UP);
				show();
				break;
				
			case '8':
				handle(VK_DOWN);
				show();
				break;
				
			case '4':
				handle(VK_LEFT);
				show();
				break;
				
			case '6':
				handle(VK_RIGHT);
				show();
				break;
				
			case '0':
				exit(1);
				break;
				
			default:
				printf("<2><4><6><8>\n");
				break;
		}
	}
	
	close(buttons_fd);
	return 0;
}
