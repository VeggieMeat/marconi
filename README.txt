Marconi is an OpenStack project designed to be an open alternative to Amazon
SQS and SNS. The Marconi module implements Openstack Marconi as an alternative
Drupal Queue backend.


Installation
------------

1. Install and enable as you would any other Drupal module.
2. Install php-opencloud library to sites/all/libraries if using the Libraries
   API module. Alternatively, php-opencloud can be installed using the
   Composer Manager module.

If you want to use Marconi as the default queue manager, add the following to
your settings.php:

  $conf['queue_default_class'] = 'MarconiQueue';

Alternatively, you can also use Marconi for specific queues:

  $conf['queue_class_{queue_name}'];


Configuration
-------------

Default configuration for all Marconi queues can be specified by setting the
marconi_default_queue variable as follows:

  $conf['marconi_default_queue'] = array(
    'credentials' => array(
      'url' => 'https://example.com/v2/identity',
      'username' => 'username',
      'password' => 'password',
      'tenantName' => 'tenant',
    ),
    'queue' => array(
      'marconi_queue_url',
    ),
  );

Specifying multiple items in the queue array will enable you to use multiple
Marconi queues.

Individual queues can override default settings by setting a variable in the
following format. Please note that any setting can be overridden this way, and
any setting that is not specified will use the relevant setting from
$conf['marconi_default_queue'].

  $conf['marconi_queue_{queue_name}'] = array(
    'queue' => array(
      'marconi_queue_url',
    ),
  );
