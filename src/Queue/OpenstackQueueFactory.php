<?php

namespace Drupal\openstack_queues\Queue;

class OpenstackQueueFactory {

  /**
   * @param string $name
   *   The name of the collection holding key and value pairs.
   *
   * @return OpenstackQueue
   */
  public function get($name) {
    return new OpenstackQueue($name);
  }

}