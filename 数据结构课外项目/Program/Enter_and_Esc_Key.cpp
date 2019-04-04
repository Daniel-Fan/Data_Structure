void Esckey()  //·µ»Ø¼ü
{
	if (His[Layer].PullDownMenu==true)
	{
		Layer--;
		puttext(His[Layer+1].left - 1, His[Layer+1].top - 1, His[Layer+1].right + 1, His[Layer+1].bottom + 1, His[Layer+1].AddrOfSaveText);
	}
}
void Enterkey()   //½øÈë¼ü
{
	int i,a[30];
	if (His[Layer].pMenu[His[Layer].MenuIndex].SubMenuItemCount != 0)
	{
		Layer++;
		His[Layer].MenuIndex = 0;
		His[Layer].MenuItemTotal = His[Layer - 1].pMenu[His[Layer - 1].MenuIndex].SubMenuItemCount;
		His[Layer].pMenu = His[Layer - 1].pMenu[His[Layer - 1].MenuIndex].SubMenuItemAddr;
		His[Layer].PullDownMenu = true;
		if (Layer==1 && His[Layer-1].MenuIndex == 7)
		{
			His[Layer].right = DownRightX-2;
			for (i = 0; i < His[Layer].MenuItemTotal; i++)
			{
				a[i] = strlen(His[Layer].pMenu[i].MenuItemStrAddr);
			}
			countmax(a, His[Layer].MenuItemTotal);
			His[Layer].left = His[Layer].right - countmax(a, His[Layer].MenuItemTotal) + 1;
		}
		else 
		{
			His[Layer].left = MainMenuItemCol[His[0].MenuIndex];
			for (i = 0; i < His[Layer].MenuItemTotal; i++)
			{
				a[i] = strlen(His[Layer].pMenu[i].MenuItemStrAddr);
			}
			countmax(a, His[Layer].MenuItemTotal);
			His[Layer].right = His[Layer].left + countmax(a, His[Layer].MenuItemTotal) - 1;
		}
		His[Layer].top = 2;
		His[Layer].bottom = His[Layer].top + His[Layer].MenuItemTotal -1;
		gettext(His[Layer].left - 1, His[Layer].top - 1, His[Layer].right + 1, His[Layer].bottom + 1, His[Layer].AddrOfSaveText);
		ShowMenu();
		His[Layer].MenuIndex = 0;
	}
}