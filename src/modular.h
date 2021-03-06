void pow_mod(t_bint* a, t_bint* b, t_bint* n,
             t_size sizeA = BLOCKS_NUMBER, t_size sizeB = 0, t_size sizeN = 0);
void mulMod(t_bint* a, t_bint* b, t_bint* n,
            t_size sizeA = BLOCKS_NUMBER, t_size sizeB = 0, t_size sizeN = 0);
void sqrMod(t_bint* a, t_bint* n,
            t_size sizeA = BLOCKS_NUMBER, t_size sizeN = 0);
void barrettMulMod(t_bint* a, t_bint* b, t_bint* n, t_bint* mu,
                   t_size sizeA, t_size sizeB, t_size sizeN, t_size sizeMu);

void barrettSqrMod(t_bint* a, t_bint* n, t_bint* mu, t_size sizeA,
                   t_size sizeN, t_size sizeMu);