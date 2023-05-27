int split (char quelle [], char ziel [], char trenner)
{
	int i = 0;

	while ((quelle[i] != trenner) && (quelle[i] != '\0') && (quelle[i] != '\n')) 
	{
		ziel [i] = quelle[i];
		i++;
	}

	ziel [i] = '\0';
	i++;

	return i;
}

