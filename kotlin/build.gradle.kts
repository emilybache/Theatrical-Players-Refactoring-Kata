plugins {
    kotlin("jvm") version "2.1.20"

}

group = "com.kata"
version = "1.0-SNAPSHOT"

java.sourceCompatibility = JavaVersion.VERSION_21

repositories {
    mavenCentral()
}

dependencies {
    testImplementation(platform("org.junit:junit-bom:5.12.2"))
    testImplementation("org.junit.jupiter:junit-jupiter")
    testRuntimeOnly("org.junit.platform:junit-platform-launcher")
    testImplementation("com.approvaltests:approvaltests:24.21.0")
}

tasks {
    test {
        useJUnitPlatform()
    }
}
