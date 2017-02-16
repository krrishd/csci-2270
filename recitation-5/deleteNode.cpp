node * DeleteNode(node *head, int value) {
    node *temp = head;
    while (temp -> next != NULL) {
        if ((temp -> next) -> value == value) {
            temp -> next = (temp -> next) -> next;
            return DeleteNode(head, value);
        } else if(head -> value == value) {
            head = head -> next;
            return DeleteNode(head, value);
        } else {
            temp = temp -> next;
        }
    }
    return head;
}