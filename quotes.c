// static t_token	*handle_quotes(char *input, int *i, char quote)
// {
// 	t_token	*token;
// 	char	*content;

// 	token = (t_token *)malloc(sizeof(t_token));
// 	if (!token)
// 		return (NULL);
// 	content = extract_quoted_content(input, i, quote);
// 	if (!content)
// 	{
// 		free(token);
// 		return (NULL);
// 	}
// 	// content = include_quotes(content, quote);
// 	token->content = ft_strdup(content);
// 	token->type = ARG;
// 	token->next = NULL;
// 	free(content);
// 	return (token);
// }

// char	*include_quotes(char *content, char quote)
// {
// 	char	*temp;
// 	size_t	i;
// 	size_t	j;

// 	i = 0;
// 	j = 0;
// 	temp = malloc((ft_strlen(content)) + 3);
// 	if (!temp)
// 	{
// 		free (content);
// 		return (NULL);
// 	}
// 	temp[i] = quote;
// 	i++;
// 	while (content[j] != '\0')
// 	{
// 		temp[i] = content[j];
// 		i++;
// 		j++;
// 	}
// 	temp[i] = quote;
// 	temp[++i] = '\0';
// 	free(content);
// 	return (temp);
// }