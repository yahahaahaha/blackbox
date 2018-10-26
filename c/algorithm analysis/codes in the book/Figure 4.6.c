static void
ListDir (DirectoryOrFile D, int Depth)
{
	if(D is a legitimate entry)
	{
		PrintName(D, Depth);
		if(D is a directory)
			for each child, C, of D
				ListDir(C, Depth + 1);
	}
}

void
ListDirectory(DirectoryOrFile D)
{
	ListDir(D, 0);
}