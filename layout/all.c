#include "all.h"

int get_internals(const char *path, char **repo, char **revision, char **internal);

// public:

int all_init(char *repo){
	return struct_build(repo);
};

int all_init_multi(int count, char **repo){
	return struct_build_multi(count, repo);
};

int all_get_file(const char *path, struct stats **stats){

	char *revision = NULL;
	char *repo = NULL;
	char *internal = NULL;

	if (get_internals(path, &repo, &revision, &internal) != 0)
		return -1;
	int result = struct_get_file(repo, revision, internal, stats);
    free(revision);
    free(repo);
    free(internal);
    return result;
	
};

char** all_get_children(const char *path){
	char *revision = NULL;
	char *repo = NULL;
	char *internal = NULL;
	
	if (get_internals(path, &repo, &revision, &internal) != 0)
		return NULL;
	char** result = struct_get_children(repo, revision, internal);
    free(revision);
    free(repo);
    free(internal);
    return result;
};

int get_internals(const char *path, char **repo, char **revision, char **internal){

	char *temp = NULL;

	(*repo) = NULL;
	(*revision) = NULL;
	(*internal) = NULL;

	if (strcmp(path, "/") == 0)
		gstrcpy(internal, "/");
	else{
		if (repo_count == 1){
			if (((*revision) = gpthprt(path, 0)) == NULL)
				return -1;
			(*internal) = gpthcut(path);
		}
		else{
			if (((*repo) = gpthprt(path, 0)) == NULL)
				return -1;
			if (((*revision) = gpthprt(path, 1)) != NULL){
				if ((temp = gpthcut(path)) == NULL){
					gstrdel(repo);
					gstrdel(revision);
					return -1;
				};
				(*internal) = gpthcut(temp);
			};
		};
	};
	return 0;

};