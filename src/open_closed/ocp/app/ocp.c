#include <stdio.h>
#include <gmodule.h>
#include "../ioc_container/container.h"
#include "../database/financial_data_mapper.h"
#include "../interactor/financial_transaction.h"

void print_transaction(gpointer data, gpointer user_data) {
    (void) user_data;

    struct financial_transaction * transaction = (struct financial_transaction *) data;
    printf("%s: %f\n", transaction->description, transaction->value);
}

int main() {

    struct resource database_resource = {
        .name = TYPE_FINANCIAL_DATA_GATEWAY,
        .alloc = (alloc_func) new_financial_data_mapper,
        .free = (free_func) free_financial_data_mapper
    };
    get_container()->register_resource(database_resource);

    struct financial_data_gateway * data_gateway = get_container()->get_resource(TYPE_FINANCIAL_DATA_GATEWAY);

    financial_transaction_list list = data_gateway->list();
    g_list_foreach(list, print_transaction, NULL);
    free_financial_transaction_list(list);

    free_container();

    return 0;
}
