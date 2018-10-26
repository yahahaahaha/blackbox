static void
SizeDirectory( DirectoryOrFile D )
{
	int TotalSize;

	TotalSize = 0;
	if( D is a legitimate entry )
	{
		TotalSize = FileSize( D );
		if( D is a directory )
			for each child, C, of D
				TotalSize += SizeDirectory( C );
	}
	r TotalSize;
}



			ch1.r			3
			ch2.r			2
			ch3.r			4
		book				10
					syl.r	1
				fall96		2
					syl.r	5
				spr97		6
					syl.r	2
				sum97		3
			cop3530			12
		course				13
		junk.c				6
	mark					30
	/usr					31