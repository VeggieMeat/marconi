Marconi is an OpenStack project designed to be an open alternative to Amazon
SQS and SNS. The Marconi module implements Openstack Marconi as an alternative
Drupal Queue backend.

Installation (via Drush - recommended)
------------

  drush dl marconi
  drush en marconi
  drush composer-manager install

Installation (Manual)
------------

1. Download and install Composer Manager module.
2. Download and install Marconi module.
3. Rebuild dependencies at admin/config/system/composer-manager.

4A. If you have Composer installed, at sites/default/files/composer run:

      composer install

4B. If you do not have Composer installed, at sites/default/files/composer run:

      curl -sS https://getcomposer.org/installer | php
      php composer.phar install

5. Check admin/config/system/composer-manager to ensure that all dependencies
   have been properly installed.

Configuration
-------------

If you want to use Marconi as the default queue manager, add the following to
your settings.php:

  $conf['queue_default_class'] = 'MarconiQueue';

Alternatively, you can also use Marconi for specific queues:

  $conf['queue_class_{queue_name}'];

Default configuration for all Marconi queues can be specified by setting the
marconi_default_queue variable as follows:

  $conf['marconi_default_queue'] = array(
    'client_id' => '00000000-0000-0000-0000-000000000000', // Optional.
    'auth_url' => 'https://example.com/v2/identity',
    'credentials' => array(
      'username' => 'username',
      'password' => 'password',
      'tenantName' => 'tenant',
    ),
    'queue' => 'marconi_queue', // Custom non-Drupal queue name. Optional.
    'region' => 'region',
    'service' => 'service',
    'provider' => 'provider', // Optional.
    'prefix' => 'my_prefix', // Optional prefix to namespace queue.
  );

The 'provider' setting is optional and can be used to load a php-opencloud
connection class specific to that provider. The 'client_id' is used to ensure
that messages are not echoed back unless explicitly requested.

For example, to use Rackspace Cloud Queues, the following settings array would
be required (assuming a queue name of 'marconi_queue' and the Chicago region):

  $conf['marconi_default_queue'] = array(
    'client_id' => '00000000-0000-0000-0000-000000000000', // Required, UUID.
    'auth_url' => 'https://identity.api.rackspacecloud.com/v2.0/',
    'credentials' => array(
      'username' => 'username',
      'apiKey' => 'API-Key',
    ),
    'region' => 'ORD',
    'service' => 'cloudQueues',
    'provider' => 'Rackspace', // There is an OpenCloud\Rackspace class
  );

As another example, HP Cloud MSGaaS would likely work with the following config-
uration (currently untested):

  $conf['marconi_default_queue'] = array(
    'auth_url' => 'https://region-a.geo-1.identity.hpcloudsvc.com:35357/v2.0/',
    'credentials' => array(
      'username' => 'username',
      'password' => 'password',
    ),
    'region' => 'region-b.geo-1',
    'service' => 'messaging',
  );

Specifying multiple items in the queue array will enable you to use multiple
Marconi queues.

Individual queues can override default settings by setting a variable in the
following format. Please note that any setting can be overridden this way, and
any setting that is not specified will use the relevant setting from
$conf['marconi_default_queue'].

  $conf['marconi_queue_{queue_name}'] = array(
    'queue' => 'my_other_queue',
  );
