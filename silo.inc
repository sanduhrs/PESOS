<?php

/**
 * @file
 * Base class for silos.
 */

use OAuth\Common\Storage\Session;
use OAuth\Common\Consumer\Credentials;

/**
 * Class Silo
 */
class Silo {

  /**
   * The consumer key.
   */
  protected $key;

  /**
   * The consumer secret.
   */
  protected $secret;

  /**
   * The callback URI.
   */
  protected $uri;

  /**
   * The silo's title.
   */
  protected $title;

  /**
   * The needed scopes.
   */
  protected $scopes;

  /**
   * The token storage.
   */
  protected $storage;

  /**
   * The service instance.
   */
  protected $service;

  /**
   * The access token.
   */
  protected $token;

  /**
   * The constructor.
   *
   * Allow to provide service settings on a central place.
   *
   * @param array $options
   */
  public function __construct($options = array()) {
    if (isset($options['key'])) {
      $this->key = $options['key'];
    }
    if (isset($options['secret'])) {
      $this->secret = $options['secret'];
    }
    if (isset($options['uri'])) {
      $this->uri = $options['uri'];
    }
    if (isset($options['title'])) {
      $this->title = $options['title'];
    }
    if (isset($options['scopes']) && is_array($options['scopes'])) {
      $this->scopes = $options['scopes'];
    }
  }

  /**
   * The key setter.
   *
   * @param string $key
   */
  public function setKey($key) {
    $this->key = $key;
  }

  /**
   * The key getter.
   *
   * @return string
   */
  public function getKey() {
    return $this->key;
  }

  /**
   * The secret setter.
   *
   * @param string $secret
   */
  public function setSecret($secret) {
    $this->secret = $secret;
  }

  /**
   * The secret getter.
   *
   * @return string
   */
  public function getSecret() {
    return $this->secret;
  }

  /**
   * The URI setter.
   *
   * @param string $uri
   */
  public function setURI($uri) {
    $this->uri = $uri;
  }

  /**
   * The URI getter.
   *
   * @return string
   */
  public function getURI() {
    return $this->uri;
  }

  /**
   * The title setter.
   *
   * @param string $title
   */
  public function setTitle($title) {
    $this->title = $title;
  }

  /**
   * The title getter.
   *
   * @return string
   */
  public function getTitle() {
    return $this->title;
  }

  /**
   * The scopes setter.
   *
   * @param array $scopes
   */
  public function setScopes($scopes) {
    $this->scopes = $scopes;
  }

  /**
   * The scopes getter.
   *
   * @return array
   */
  public function getScopes() {
    return $this->scopes;
  }

  /**
   * Initialize the authentication.
   */
  public function authenticate() {
    /** @var $serviceFactory \OAuth\ServiceFactory An OAuth service factory. */
    $serviceFactory = new \OAuth\ServiceFactory();

    // Setup the credentials for the requests
    $this->credentials = new Credentials(
      $this->key,
      $this->secret,
      $this->uri
    );

    // Session storage
    $this->storage = new Session();

    // Instantiate the service
    /** @var $gitHub GitHub */
    $this->service = $serviceFactory->createService(
      $this->title,
      $this->credentials,
      $this->storage,
      $this->scopes
    );
  }

}
