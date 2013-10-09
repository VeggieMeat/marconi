<?php

/**
 * @file
 * Contains MarconiQueue class implementing DrupalQueueInterface
 */

class MarconiQueue implements DrupalQueueInterface {

  /**
   * Start working with a queue.
   *
   * @param string name
   *   The name of the queue to work with.
   */

  public function __construct($name) {
    if (marconi_loaded()) {
      $this->name = $name;
      $this->params = marconi_get_queue_options($name);
      $this->connect();
    }
  }

  /**
   * Create a queue.
   *
   * @TODO Determine if this is possible remotely, and if not submit a pull
   * request to php-opencloud project implementing this functionality.
   */
  public function createQueue() {
  }

  /**
   * Delete a queue.
   *
   * @TODO Determine if this is possible remotely, and if not submit a pull
   * request to php-opencloud project implementing this functionality.
   */
  public function deleteQueue() {
  }

  /**
   * Add a queue item and store it directly to the queue.
   *
   * @param object $data
   *   Arbitrary data to be associated with the new task in the queue.
   *
   * @return bool
   */
  public function createItem($data) {

  }

  /**
   * Connect to a Marconi queue.
   */
  private function connect() {
    $params = $this->params;
    $class = 'OpenCloud\\' . $params['provider'];
    if (!class_exists($class)) {
      $class = 'OpenCloud\OpenStack';
    }
    $this->connection = new $class($params['auth_url'], $params['credentials']);
    $this->service = new OpenCloud\Queues\Service($this->connection, $params['service'], $params['region']);
    $this->service->setClientId($params['client_id']);
  }
}
