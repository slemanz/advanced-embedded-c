# Publisher-Subscriber Pattern

Also known as observer.

## Abstract

The pattern is a messaging architecture designed to facilitate asynchronous communication
between components within a system, particularly in embedded applications. This pattern
allows publishers to emit messages without needing to know which components are receiving
them, thus promoting loose coupling.

## Problem

Additionally, managing how messages are sent and received can become complex, especially
in environments with limited resources. The Publisher-Subscriber pattern addresses these
issues by decoupling the message producers from consumers.

## Pattern Structure

The pattern structure consists of several key components: publishers, subscribers, and
optionally a broker. Publishers are responsible for generating and releasing messages to
any interested parties without awareness of who those parties are. Subscribers express
interest in certain messages and implement logic to handle them when received. A broker,
while not always necessary, acts as an intermediary that manages subscriptions and routes
messages between publishers and subscribers.

## Implementation Example

