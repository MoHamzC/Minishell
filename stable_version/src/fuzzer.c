#include "minishell.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
	char *input = malloc(size+1);
	ft_memcpy(input, data, size);
	input[size] = 0;

    t_shell shell;
    shell.env = NULL;

    // functions to test
    t_token **tokens = take_ur_token_and_leave_me_alone(input, &shell);
    free_tokens(tokens);

	free(input);

	return 0;
}