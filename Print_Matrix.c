//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    printf("Matrix C:\n");
     for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d\t", c[i][j]);
        }
        printf("\n");
    }
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    printf("Matrix A:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d\t", a[i][j]);
        }
        printf("\n");
    }
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
     printf("Matrix B:\n");
     for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d\t", b[i][j]);
        }
        printf("\n");
    }

    return 0;
}
