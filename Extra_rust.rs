use std::time::{Instant}; //bibliteca para medir o tempo decorrido
use rand::SeedableRng; // importa o trait SeedableRng que é utilizado para inicializar geradores de números aleatórios
use rand::distributions::{Distribution, Uniform}; //  importa os tipos e traits relacionados à distribuição de números aleatórios
use rand::rngs::SmallRng; // importa o tipo SmallRng que é um gerador de números aleatórios rápido
use ndarray::Array2; //importa Array2 usado para representar matriz bidimensional 

fn main() {
    let n = 8192; // define o tamanho da matriz
    // foram usados n = 1024, 2048, 4096 e 8192

    let mut rng = SmallRng::from_entropy(); // inicializa um gerador de números aleatórios
    let matrix1 = generate_random_matrix(n, &mut rng); // chama a função que preenche matriz 1

    let matrix2 = generate_random_matrix(n, &mut rng); // chama a função que preenche matriz 2

    let start_time = Instant::now(); // começa uma contagem de tempo
    let _result_matrix = multiply_matrices(&matrix1, &matrix2); // chama a função de multiplicar matriz
    let elapsed_time = start_time.elapsed(); // para a contagem do tempo

    println!("Tempo decorrido para a multiplicação das matrizes: {:?}", elapsed_time); // imprime o tempo decorrido
}

fn generate_random_matrix(n: usize, rng: &mut SmallRng) -> Array2<f64> { // função que gera as matrizes aleatórias
    let distribution = Uniform::new(1.0, 50.0); // variável que pegará um valor aleatório entre 1.0 e 50.0
    Array2::from_shape_fn((n, n), |_| distribution.sample(rng)) // gera a matriz aleatória usando a variável anterior
}

fn multiply_matrices(matrix1: &Array2<f64>, matrix2: &Array2<f64>) -> Array2<f64> { // função que fará a multiplicação das matrizes
    matrix1.dot(matrix2) // retorna o resultado da matriz 1 com a matriz 2
}
