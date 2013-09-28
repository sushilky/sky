/*Write your custom functions here if any */



node * sortList(node *l1){

/* For your reference
	struct node{

	struct node * next;
	int val;
      };
The above structure has already been declared, please do NOT redeclare the structure
*/

    if(ll == NULL || ll->next == NULL)
        return ll;

    node *p = ll->next;
    node *tmp = ll;

    while(p != NULL && p->val >= tmp->val){
        p = p->next;
        tmp = tmp->next;
    }
    if(p==NULL)
        return ll;

    //tmp is First part Sorted End
    node *L1HEAD = ll;
    node *L1TAIL = tmp;
    node *L2HEAD = p;
    L1TAIL->next = NULL;

    node *merged_ll = NULL;
    node *merged_ll_tail = NULL;

    if(L1HEAD->val < L2HEAD->val){
        merged_ll_tail = L1HEAD;
        merged_ll = L1HEAD;
        L1HEAD = L1HEAD->next;
    }
    else{
        merged_ll_tail = L2HEAD;
        merged_ll = L2HEAD;
        L2HEAD = L2HEAD->next;
    }

    while(L1HEAD != NULL && L2HEAD != NULL){
        if(L1HEAD->val < L2HEAD->val){
            merged_ll_tail->next = L1HEAD;
            L1HEAD = L1HEAD->next;
            merged_ll_tail->next = NULL;
        }
        else{
            merged_ll_tail->next = L2HEAD;
            L2HEAD = L2HEAD->next;
            merged_ll_tail->next = NULL;
        }
    }

    if(L1HEAD != NULL){
            merged_ll_tail->next = L1HEAD;
    }

    if (L2HEAD != NULL) {
            merged_ll_tail->next = L2HEAD;
    }

    return merged_ll;
}

