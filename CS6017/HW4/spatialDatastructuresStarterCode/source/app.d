import std.stdio;

import common;
import dumbknn;
import bucketknn;
import quadtree;
import kdtree;
//import your files here

struct Result {
    int dimension, k, n;
    ulong time;
}

auto dumbKnnUniform() {
    writeln("dumbKNN results");
    int[] numberPoints = [100, 1000, 10000, 100000];
    int[] numberPointsToGet = [2, 4, 8, 10, 16];
    Result[] dumbKnnResults;

    static foreach (dim; 1..8) { // for each dimensions 1 to 7
        foreach (N; numberPoints) { // test each number of points
            //get points of the appropriate dimension
            auto trainingPoints = getUniformPoints!dim(N);
            auto testingPoints = getUniformPoints!dim(100);

            auto kd = DumbKNN!dim(trainingPoints);
            auto sw = StopWatch(AutoStart.no);
            foreach (k; numberPointsToGet) { // and for the diff # of points, change # pts k to find
                sw.start; //start my stopwatch

                foreach (const ref qp; testingPoints) {
                    kd.knnQuery(qp, k);
                }
                sw.stop;
                // store results in array
                Result newResult;
                newResult.dimension = dim;
                newResult.k = k;
                newResult.n = N;
                newResult.time = sw.peek.total!"usecs";
                dumbKnnResults ~= newResult;
            }
        }
    }

    auto file1 = File("dumbKnnUniform.csv", "w");
    file1.writeln("structureName,dimension,k,n,time");
    foreach (result; dumbKnnResults) {
        file1.writefln("dumbKNN,%d,%d,%d,%d", result.dimension, result.k, result.n, result.time);
    }
    file1.close();
}

auto dumbKnnGaussian() {
    writeln("dumbKNN results: Gaussian");
    int[] numberPoints = [100, 1000, 10000, 100000];
    int[] numberPointsToGet = [2, 4, 8, 10, 16];
    Result[] dumbKnnResults;

    static foreach (dim; 1..8) { // for each dimensions 1 to 7
        foreach (N; numberPoints) { // test each number of points
            //get points of the appropriate dimension
            auto trainingPoints = getGaussianPoints!dim(N);
            auto testingPoints = getGaussianPoints!dim(100);

            auto kd = DumbKNN!dim(trainingPoints);
            auto sw = StopWatch(AutoStart.no);
            foreach (k; numberPointsToGet) { // and for the diff # of points, change # pts k to find
                sw.start; //start my stopwatch

                foreach (const ref qp; testingPoints) {
                    kd.knnQuery(qp, k);
                }
                sw.stop;
                // store results in array
                Result newResult;
                newResult.dimension = dim;
                newResult.k = k;
                newResult.n = N;
                newResult.time = sw.peek.total!"usecs";
                dumbKnnResults ~= newResult;
            }
        }
    }

    auto file1 = File("dumbKnnGaussian.csv", "w");
    file1.writeln("structureName,dimension,k,n,time");
    foreach (result; dumbKnnResults) {
        file1.writefln("dumbKNN,%d,%d,%d,%d", result.dimension, result.k, result.n, result.time);
    }
    file1.close();
}

auto bucketKnnUniform() {
    writeln("bucketKNN results: uniform");
    int[] numberPoints = [100, 1000, 10000, 100000];
    int[] numberPointsToGet = [2, 4, 8, 10, 16];
    Result[] bucketKnnResults;

    static foreach (dim; 1..8) { // for each dimensions 1 to 7
        foreach (N; numberPoints) { // test each number of points
            //get points of the appropriate dimension
            auto trainingPoints = getUniformPoints!dim(N);
            auto testingPoints = getUniformPoints!dim(100);

            auto kd = BucketKNN!dim(trainingPoints, cast(int)pow(N / 64, 1.0 / dim));
            auto sw = StopWatch(AutoStart.no);
            foreach (k; numberPointsToGet) { // and for the diff # of points, change # pts k to find
                sw.start; //start my stopwatch

                foreach (const ref qp; testingPoints) {
                    kd.knnQuery(qp, k);
                }
                sw.stop;
                // store results in array
                Result newResult;
                newResult.dimension = dim;
                newResult.k = k;
                newResult.n = N;
                newResult.time = sw.peek.total!"usecs";
                bucketKnnResults ~= newResult;
            }
        }
    }

    auto file1 = File("bucketKnnUniform.csv", "w");
    file1.writeln("structureName,dimension,k,n,time");
    foreach (result; bucketKnnResults) {
        file1.writefln("bucketKNN,%d,%d,%d,%d", result.dimension, result.k, result.n, result.time);
    }
    file1.close();
}

auto bucketKnnGaussian() {
    writeln("bucketKnn results: Gaussian");
    int[] numberPoints = [100, 1000, 10000, 100000];
    int[] numberPointsToGet = [2, 4, 8, 10, 16];
    Result[] bucketKnnResults;

    static foreach (dim; 1..8) { // for each dimensions 1 to 7
        foreach (N; numberPoints) { // test each number of points
            //get points of the appropriate dimension
            auto trainingPoints = getGaussianPoints!dim(N);
            auto testingPoints = getGaussianPoints!dim(100);

            auto kd = BucketKNN!dim(trainingPoints, cast(int)pow(N / 64, 1.0 / dim));
            auto sw = StopWatch(AutoStart.no);
            foreach (k; numberPointsToGet) { // and for the diff # of points, change # pts k to find
                sw.start; //start my stopwatch

                foreach (const ref qp; testingPoints) {
                    kd.knnQuery(qp, k);
                }
                sw.stop;
                // store results in array
                Result newResult;
                newResult.dimension = dim;
                newResult.k = k;
                newResult.n = N;
                newResult.time = sw.peek.total!"usecs";
                bucketKnnResults ~= newResult;
            }
        }
    }

    auto file1 = File("bucketKnnGaussian.csv", "w");
    file1.writeln("structureName,dimension,k,n,time");
    foreach (result; bucketKnnResults) {
        file1.writefln("bucketKNN,%d,%d,%d,%d", result.dimension, result.k, result.n, result.time);
    }
    file1.close();
}

auto quadTreeUniform() {
    writeln("quad tree results: uniform");
    int[] numberPoints = [100, 1000, 10000, 100000];
    int[] numberPointsToGet = [2, 4, 8, 10, 16];
    Result[] quadTreeResults;

    static foreach (dim; 2..3) { // for each dimensions 2 to 3
        foreach (N; numberPoints) { // test each number of points
            //get points of the appropriate dimension
            auto trainingPoints = getUniformPoints!dim(N);
            auto testingPoints = getUniformPoints!dim(100);

            auto kd = QuadTree!dim(trainingPoints);
            auto sw = StopWatch(AutoStart.no);
            foreach (k; numberPointsToGet) { // and for the diff # of points, change # pts k to find
                sw.start; //start my stopwatch

                foreach (const ref qp; testingPoints) {
                    kd.knnQuery(qp, k);
                }
                sw.stop;
                // store results in array
                Result newResult;
                newResult.dimension = dim;
                newResult.k = k;
                newResult.n = N;
                newResult.time = sw.peek.total!"usecs";
                quadTreeResults ~= newResult;
            }
        }
    }

    auto file1 = File("quadTreeUniform.csv", "w");
    file1.writeln("structureName,dimension,k,n,time");
    foreach (result; quadTreeResults) {
        file1.writefln("quadTree,%d,%d,%d,%d", result.dimension, result.k, result.n, result.time);
    }
    file1.close();
}

auto quadTreeGaussian() {
    writeln("quad tree results: Gaussian");
    int[] numberPoints = [100, 1000, 10000, 100000];
    int[] numberPointsToGet = [2, 4, 8, 10, 16];
    Result[] quadTreeResults;

    static foreach (dim; 2..3) { // for each dimensions 2 to 3
        foreach (N; numberPoints) { // test each number of points
            //get points of the appropriate dimension
            auto trainingPoints = getGaussianPoints!dim(N);
            auto testingPoints = getGaussianPoints!dim(100);

            auto kd = QuadTree!dim(trainingPoints);
            auto sw = StopWatch(AutoStart.no);
            foreach (k; numberPointsToGet) { // and for the diff # of points, change # pts k to find
                sw.start; //start my stopwatch

                foreach (const ref qp; testingPoints) {
                    kd.knnQuery(qp, k);
                }
                sw.stop;
                // store results in array
                Result newResult;
                newResult.dimension = dim;
                newResult.k = k;
                newResult.n = N;
                newResult.time = sw.peek.total!"usecs";
                quadTreeResults ~= newResult;
            }
        }
    }

    auto file1 = File("quadTreeGaussian.csv", "w");
    file1.writeln("structureName,dimension,k,n,time");
    foreach (result; quadTreeResults) {
        file1.writefln("quadTree,%d,%d,%d,%d", result.dimension, result.k, result.n, result.time);
    }
    file1.close();
}

auto kdTreeUniform() {
    writeln("kdTree results: uniform");
    int[] numberPoints = [100, 1000, 10000, 100000];
    int[] numberPointsToGet = [2, 4, 8, 10, 16];
    Result[] kdTreeResults;

    static foreach (dim; 1..8) { // for each dimensions 1 to 7
        foreach (N; numberPoints) { // test each number of points
            //get points of the appropriate dimension
            auto trainingPoints = getUniformPoints!dim(N);
            auto testingPoints = getUniformPoints!dim(100);

            auto kd = KDTree!dim(trainingPoints);
            auto sw = StopWatch(AutoStart.no);
            foreach (k; numberPointsToGet) { // and for the diff # of points, change # pts k to find
                sw.start; //start my stopwatch

                foreach (const ref qp; testingPoints) {
                    kd.knnQuery(qp, k);
                }
                sw.stop;
                // store results in array
                Result newResult;
                newResult.dimension = dim;
                newResult.k = k;
                newResult.n = N;
                newResult.time = sw.peek.total!"usecs";
                kdTreeResults ~= newResult;
            }
        }
    }

    auto file1 = File("kdTreeUniform.csv", "w");
    file1.writeln("structureName,dimension,k,n,time");
    foreach (result; kdTreeResults) {
        file1.writefln("kdTree,%d,%d,%d,%d", result.dimension, result.k, result.n, result.time);
    }
    file1.close();
}

auto kdTreeGaussian() {
    writeln("kdTree results: Gaussian");
    int[] numberPoints = [100, 1000, 10000, 100000];
    int[] numberPointsToGet = [2, 4, 8, 10, 16];
    Result[] kdTreeResults;

    static foreach (dim; 1..8) { // for each dimensions 1 to 7
        foreach (N; numberPoints) { // test each number of points
            //get points of the appropriate dimension
            auto trainingPoints = getGaussianPoints!dim(N);
            auto testingPoints = getGaussianPoints!dim(100);

            auto kd = KDTree!dim(trainingPoints);
            auto sw = StopWatch(AutoStart.no);
            foreach (k; numberPointsToGet) { // and for the diff # of points, change # pts k to find
                sw.start; //start my stopwatch

                foreach (const ref qp; testingPoints) {
                    kd.knnQuery(qp, k);
                }
                sw.stop;
                // store results in array
                Result newResult;
                newResult.dimension = dim;
                newResult.k = k;
                newResult.n = N;
                newResult.time = sw.peek.total!"usecs";
                kdTreeResults ~= newResult;
            }
        }
    }

    auto file1 = File("kdTreeGaussian.csv", "w");
    file1.writeln("structureName,dimension,k,n,time");
    foreach (result; kdTreeResults) {
        file1.writefln("kdTree,%d,%d,%d,%d", result.dimension, result.k, result.n, result.time);
    }
    file1.close();
}

void main() {
    dumbKnnUniform();
    dumbKnnGaussian();
    bucketKnnUniform();
    bucketKnnGaussian();
    quadTreeUniform();
    quadTreeGaussian();
    kdTreeUniform();
    kdTreeGaussian();
}
