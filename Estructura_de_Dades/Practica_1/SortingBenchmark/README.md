* To include [junit](https://junit.org/junit5/) libraries:

    * Put cursor over a @Test (which is marked in red)
        * Alt-enter
        * Add JUnit 5.* to classpath

* To include [jmh](https://openjdk.java.net/projects/code-tools/jmh/) libraries:

    * Project structure
        * Libraries
            * (+) from maven
                - org.openjdk.jmh:jmh-core:1.25.2
                - org.openjdk.jmh:jmh-generator-annprocess:1.25.2
            (each time we say OK, ADD to module)
        
    * Preferences
        * Build, Execution, Deployment
            * Compiler
                * Annotation processor
                    - Enable Annotation Processor 

* Reading:

    - Code Tools: jmh
        - https://openjdk.java.net/projects/code-tools/jmh/
    - Avoiding Benchmarking Pitfalls on the JVM
        - https://www.oracle.com/technical-resources/articles/java/architect-benchmarking.html
    - Java Microbenchmarks with JMH, Part 1
        - https://blog.avenuecode.com/java-microbenchmarks-with-jmh-part-1
    - Java Microbenchmarks with JMH, Part 2
        - https://blog.avenuecode.com/java-microbenchmarks-with-jmh-part-2
    - Java Microbenchmarks with JMH, Part 3
        - https://blog.avenuecode.com/java-microbenchmarks-with-jmh-part-3