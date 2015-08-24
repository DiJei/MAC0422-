#define MAXCOMMAND 50

void bufferClean(char *buffer, int size);
void listClean(char **list);
void getArguments(char *line,char command[], char **arguments);
int striComp(char *str, char *comp, int size);